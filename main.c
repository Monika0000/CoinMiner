#include <stdio.h>
#include <malloc.h>

#include "sha1.h"

int main() {
    const char* input = "[11111111111111111111111111111111111111111111111111111111111111]\0";

    /*char* str = (char*)malloc(4);
    str[0] = 'w';
    str[1] = 'o';
    str[2] = 'r';
    str[3] = 'd';
    append(str, 'q', 4, 4);
    realloc(str, 9);
    str[8] = '\0';
    printf("%s", str);*/

    struct sha1* checksum = newSHA1();

    update(checksum, input);

    char* hash = final(checksum);

    realloc(hash, 65);
    hash[64] = '\0';
    printf(hash);

    //printf("end\n");

    //print_char_array(hash, 60);

    //if (hash){
        //printf("%s", hash);
    free(hash);
    //}

    free(checksum);

    return 0;
}
