#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "dccnet.h"

void* receiver_thread(void* arg) {
    uint8_t buffer[1024];
    while (1) {
        int len = dccnet_read(buffer, sizeof(buffer));
        if (len > 0) {
            buffer[len] = '\0';
            printf("[RECEBIDO]: %s\n", buffer);
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <host> <porta>\n", argv[0]);
        exit(1);
    }

    dccnet_connect(argv[1], atoi(argv[2]));
    dccnet_init_receiver();

    pthread_t recv_tid;
    pthread_create(&recv_tid, NULL, receiver_thread, NULL);

    char linha[1024];
    while (fgets(linha, sizeof(linha), stdin)) {
        int len = strlen(linha);
        if (linha[len - 1] == '\n') linha[len - 1] = '\0';
        dccnet_send((uint8_t*)linha, strlen(linha));
    }

    return 0;
}
