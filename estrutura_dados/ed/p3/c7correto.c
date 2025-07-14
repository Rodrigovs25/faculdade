#include <stdlib.h>
#include <stdint.h>

int main() {
    char* alphabet = calloc(26, sizeof(char));

    for(uint8_t i = 0; i < 26; i++) {
        *(alphabet + i) = 'A' + i;
    }

    free(alphabet);
    return 0;
}
