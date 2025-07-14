#include "dccnet.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <arpa/inet.h>

static DccnetContext context;

void dccnet_init(int sockfd) {
    context.sockfd = sockfd;
    context.next_seq = 0;
    context.expected_seq = 0;
}

void dccnet_close() {
    // Envia um quadro FIM
    uint8_t fim_type = DCCNET_FIM;
    dccnet_send(&fim_type, 0);
}

static uint16_t internet_checksum(const uint8_t *data, size_t len) {
    uint32_t sum = 0;

    for (size_t i = 0; i < len; i += 2) {
        uint16_t word = data[i] << 8;
        if (i + 1 < len)
            word |= data[i + 1];
        sum += word;
    }

    // Adiciona overflow
    while (sum >> 16)
        sum = (sum & 0xFFFF) + (sum >> 16);

    return ~sum;
}

int dccnet_send(uint8_t *data, uint16_t length) {
    uint8_t frame[2 * (3 + DCCNET_MAX_PAYLOAD + 2) + 2]; // FLAG + TYPE+SEQ+LEN + PAYLOAD + CHKSUM + FLAG + escaping
    size_t pos = 0;

    uint8_t header[3];
    header[0] = DCCNET_DATA;
    header[1] = context.next_seq;
    header[2] = length;

    // Monta o quadro bruto para cálculo do checksum
    uint8_t raw_frame[3 + length];
    memcpy(raw_frame, header, 3);
    memcpy(raw_frame + 3, data, length);

    uint16_t chksum = internet_checksum(raw_frame, 3 + length);

    // Início do enquadramento
    frame[pos++] = DCCNET_FLAG;

    // Adiciona header, payload e checksum com escape
    for (size_t i = 0; i < 3 + length; i++) {
        uint8_t byte = raw_frame[i];
        if (byte == DCCNET_FLAG || byte == DCCNET_ESC) {
            frame[pos++] = DCCNET_ESC;
            frame[pos++] = byte ^ DCCNET_ESC_XOR;
        } else {
            frame[pos++] = byte;
        }
    }

    // Adiciona o checksum (2 bytes)
    for (int i = 0; i < 2; i++) {
        uint8_t byte = (chksum >> (8 * (1 - i))) & 0xFF;
        if (byte == DCCNET_FLAG || byte == DCCNET_ESC) {
            frame[pos++] = DCCNET_ESC;
            frame[pos++] = byte ^ DCCNET_ESC_XOR;
        } else {
            frame[pos++] = byte;
        }
    }

    // Finaliza com FLAG
    frame[pos++] = DCCNET_FLAG;

    // Envio com parada e espera (aguarda ACK)
    ssize_t sent = send(context.sockfd, frame, pos, 0);
    if (sent < 0) return -1;

    // Espera por ACK
    fd_set fds;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = DCCNET_TIMEOUT_MS * 1000;

    FD_ZERO(&fds);
    FD_SET(context.sockfd, &fds);

    if (select(context.sockfd + 1, &fds, NULL, NULL, &tv) > 0) {
        uint8_t recvbuf[32];
        ssize_t recv_len = recv(context.sockfd, recvbuf, sizeof(recvbuf), 0);

        if (recv_len >= 5 && recvbuf[0] == DCCNET_FLAG && recvbuf[recv_len - 1] == DCCNET_FLAG) {
            // Decodifica para verificar ACK
            for (ssize_t i = 1; i < recv_len - 1; i++) {
                if (recvbuf[i] == DCCNET_ESC) {
                    recvbuf[i] = recvbuf[i + 1] ^ DCCNET_ESC_XOR;
                    memmove(&recvbuf[i + 1], &recvbuf[i + 2], recv_len - i - 2);
                    recv_len--;
                }
            }
            if (recvbuf[1] == DCCNET_ACK && recvbuf[2] == context.next_seq) {
                context.next_seq ^= 1;
                return length;
            }
        }
    }

    // Timeout ou erro no ACK
    return -1;
}

int dccnet_recv(uint8_t *buffer, uint16_t max_length) {
    uint8_t frame[2 * (3 + DCCNET_MAX_PAYLOAD + 2) + 2];
    size_t pos = 0;
    int in_frame = 0;

    while (1) {
        uint8_t byte;
        ssize_t r = recv(context.sockfd, &byte, 1, 0);
        if (r <= 0) return -1;

        if (byte == DCCNET_FLAG) {
            if (in_frame && pos >= 5) {
                // Decodificar frame
                uint8_t decoded[3 + DCCNET_MAX_PAYLOAD + 2];
                size_t dpos = 0;

                for (size_t i = 0; i < pos; i++) {
                    if (frame[i] == DCCNET_ESC) {
                        decoded[dpos++] = frame[++i] ^ DCCNET_ESC_XOR;
                    } else {
                        decoded[dpos++] = frame[i];
                    }
                }

                uint8_t type = decoded[0];
                uint8_t seq = decoded[1];
                uint8_t len = decoded[2];

                if (type == DCCNET_DATA && seq == context.expected_seq && len <= max_length) {
                    uint16_t received_checksum = (decoded[3 + len] << 8) | decoded[3 + len + 1];
                    uint16_t calc_checksum = internet_checksum(decoded, 3 + len);

                    if (received_checksum == calc_checksum) {
                        memcpy(buffer, decoded + 3, len);

                        // Envia ACK
                        uint8_t ack_frame[6] = { DCCNET_FLAG, DCCNET_ACK, seq, 0, 0, DCCNET_FLAG };
                        uint16_t ack_checksum = internet_checksum(&ack_frame[1], 2);
                        ack_frame[3] = (ack_checksum >> 8) & 0xFF;
                        ack_frame[4] = ack_checksum & 0xFF;
                        send(context.sockfd, ack_frame, 6, 0);

                        context.expected_seq ^= 1;
                        return len;
                    }
                }

                pos = 0;
            } else {
                in_frame = 1;
                pos = 0;
            }
        } else if (in_frame) {
            frame[pos++] = byte;
            if (pos >= sizeof(frame)) pos = 0; // descarta se muito grande
        }
    }
}
