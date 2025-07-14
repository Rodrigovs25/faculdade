#ifndef DCCNET_H
#define DCCNET_H

#include <stdint.h>

#define DCCNET_FLAG     0x7E  // delimitador de quadro
#define DCCNET_ESC      0x7D  // escape
#define DCCNET_ESC_XOR  0x20  // para escaping de FLAG e ESC

#define DCCNET_DATA     0x01
#define DCCNET_ACK      0x02
#define DCCNET_FIM      0x03

#define DCCNET_TIMEOUT_MS 1000  // timeout para ACK

#define DCCNET_MAX_PAYLOAD 1024

typedef struct {
    int sockfd;             // socket TCP
    uint8_t next_seq;       // sequência esperada para envio (0 ou 1)
    uint8_t expected_seq;   // sequência esperada na recepção
} DccnetContext;

// Inicialização
void dccnet_init(int sockfd);
void dccnet_close();

// Enviar e receber dados (com stop-and-wait)
int dccnet_send(uint8_t *data, uint16_t length);
int dccnet_recv(uint8_t *buffer, uint16_t max_length);

#endif // DCCNET_H
