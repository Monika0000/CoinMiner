#include <stdio.h>
#include <malloc.h>

#include "sha1.h"

int main() {
    const char* input = "[11111111111111111111111111111111111111111111111111111111111111]dadsadad1\0";

    struct sha1* checksum = newSHA1();

    while (1) {
        update(checksum, input);

        char *hash = final(checksum);

        printf(hash); printf("\n"); free(hash);

        reset(checksum);
    }

    free(checksum);

    return 0;
}
