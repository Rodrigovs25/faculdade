#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "dccnet.h"

void* receiver_thread(void* arg) {
    uint8_t buffer[1024], resposta[1050];
    while (1) {
        int len = dccnet_read(buffer, sizeof(buffer));
        if (len > 0) {
            buffer[len] = '\0';
            printf("[RECEBIDO]: %s\n", buffer);

            snprintf((char*)resposta, sizeof(resposta), "ACK: %s", buffer);
            dccnet_send(resposta, strlen((char*)resposta));
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <porta>\n", argv[0]);
        exit(1);
    }

    dccnet_listen(atoi(argv[1]));
    dccnet_init_receiver();

    pthread_t recv_tid;
    pthread_create(&recv_tid, NULL, receiver_thread, NULL);

    // Apenas espera. Toda lógica está na thread de recepção.
    while (1) {
        sleep(1);
    }

    return 0;
}
