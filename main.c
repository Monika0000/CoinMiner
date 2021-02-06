#include <stdio.h>
#include <malloc.h>

#include "sha1.h"

int main() {
    const char* input = "[11111111111111111111111111111111111111111111111111111111111111]\0";

    struct sha1* checksum = newSHA1();

    char* hash = (char*)malloc(BLOCK_BYTES + 1);

    for (unsigned int i = 0; i < 10000000; i++) {
        update(checksum, input);

        //char *hash = final(checksum);
        final(checksum, hash);

        printf(hash); printf("\n");
        reset(checksum);
    }

    free(hash);
    free(checksum);

    return 0;
}
