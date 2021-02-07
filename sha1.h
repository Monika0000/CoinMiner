//
// Created by Nikita on 05.02.2021.
//

#ifndef COINMINER_SHA1_H
#define COINMINER_SHA1_H

#include "sha1_util.h"
#include "string_util.h"

struct sha1 {
    unsigned __int32 digest[5];
    char* buffer;
    unsigned __int64 transforms;
    unsigned __int32 buff_size;
};

inline static void reset(struct sha1* _sha1){
    _sha1->digest[0] = 0x67452301;
    _sha1->digest[1] = 0xefcdab89;
    _sha1->digest[2] = 0x98badcfe;
    _sha1->digest[3] = 0x10325476;
    _sha1->digest[4] = 0xc3d2e1f0;
    if (_sha1->buffer)
        free(_sha1->buffer);
    _sha1->buffer = NULL;
    /* Reset counters */
    _sha1->buff_size = 0;
    _sha1->transforms = 0;
}

inline static struct sha1* newSHA1() {
    struct sha1* _sha1 = (struct sha1*)malloc(sizeof(struct sha1));
    _sha1->buffer = NULL;
    reset(_sha1);
    return _sha1;
}

char * string_copy( const char *from, char *to ) {
    for ( char *p = to; ( *p = *from ) != '\0'; ++p, ++from)
    {
        ;
    }
}

inline static void copySHA1(struct sha1* from, struct sha1* to) {
    string_copy(from->buffer, to->buffer);
    to->buff_size = from->buff_size;
    to->digest[0] = from->digest[0];
    to->digest[1] = from->digest[1];
    to->digest[2] = from->digest[2];
    to->digest[3] = from->digest[3];
    to->digest[4] = from->digest[4];
    to->transforms = from->transforms;
}

inline static void transform(struct sha1* sha1, unsigned __int32 block[BLOCK_INTS]){
    /* Copy digest[] to working vars */
    unsigned __int32 a = sha1->digest[0];
    unsigned __int32 b = sha1->digest[1];
    unsigned __int32 c = sha1->digest[2];
    unsigned __int32 d = sha1->digest[3];
    unsigned __int32 e = sha1->digest[4];

    /* 4 rounds of 20 operations each. Loop unrolled. */
    R0(block, a, &b, c, d, &e,  0);
    R0(block, e, &a, b, c, &d,  1);
    R0(block, d, &e, a, b, &c,  2);
    R0(block, c, &d, e, a, &b,  3);
    R0(block, b, &c, d, e, &a,  4);
    R0(block, a, &b, c, d, &e,  5);
    R0(block, e, &a, b, c, &d,  6);
    R0(block, d, &e, a, b, &c,  7);
    R0(block, c, &d, e, a, &b,  8);
    R0(block, b, &c, d, e, &a,  9);
    R0(block, a, &b, c, d, &e, 10);
    R0(block, e, &a, b, c, &d, 11);
    R0(block, d, &e, a, b, &c, 12);
    R0(block, c, &d, e, a, &b, 13);
    R0(block, b, &c, d, e, &a, 14);
    R0(block, a, &b, c, d, &e, 15);
    R1(block, e, &a, b, c, &d,  0);
    R1(block, d, &e, a, b, &c,  1);
    R1(block, c, &d, e, a, &b,  2);
    R1(block, b, &c, d, e, &a,  3);
    R2(block, a, &b, c, d, &e,  4);
    R2(block, e, &a, b, c, &d,  5);
    R2(block, d, &e, a, b, &c,  6);
    R2(block, c, &d, e, a, &b,  7);
    R2(block, b, &c, d, e, &a,  8);
    R2(block, a, &b, c, d, &e,  9);
    R2(block, e, &a, b, c, &d, 10);
    R2(block, d, &e, a, b, &c, 11);
    R2(block, c, &d, e, a, &b, 12);
    R2(block, b, &c, d, e, &a, 13);
    R2(block, a, &b, c, d, &e, 14);
    R2(block, e, &a, b, c, &d, 15);
    R2(block, d, &e, a, b, &c,  0);
    R2(block, c, &d, e, a, &b,  1);
    R2(block, b, &c, d, e, &a,  2);
    R2(block, a, &b, c, d, &e,  3);
    R2(block, e, &a, b, c, &d,  4);
    R2(block, d, &e, a, b, &c,  5);
    R2(block, c, &d, e, a, &b,  6);
    R2(block, b, &c, d, e, &a,  7);
    R3(block, a, &b, c, d, &e,  8);
    R3(block, e, &a, b, c, &d,  9);
    R3(block, d, &e, a, b, &c, 10);
    R3(block, c, &d, e, a, &b, 11);
    R3(block, b, &c, d, e, &a, 12);
    R3(block, a, &b, c, d, &e, 13);
    R3(block, e, &a, b, c, &d, 14);
    R3(block, d, &e, a, b, &c, 15);
    R3(block, c, &d, e, a, &b,  0);
    R3(block, b, &c, d, e, &a,  1);
    R3(block, a, &b, c, d, &e,  2);
    R3(block, e, &a, b, c, &d,  3);
    R3(block, d, &e, a, b, &c,  4);
    R3(block, c, &d, e, a, &b,  5);
    R3(block, b, &c, d, e, &a,  6);
    R3(block, a, &b, c, d, &e,  7);
    R3(block, e, &a, b, c, &d,  8);
    R3(block, d, &e, a, b, &c,  9);
    R3(block, c, &d, e, a, &b, 10);
    R3(block, b, &c, d, e, &a, 11);
    R4(block, a, &b, c, d, &e, 12);
    R4(block, e, &a, b, c, &d, 13);
    R4(block, d, &e, a, b, &c, 14);
    R4(block, c, &d, e, a, &b, 15);
    R4(block, b, &c, d, e, &a,  0);
    R4(block, a, &b, c, d, &e,  1);
    R4(block, e, &a, b, c, &d,  2);
    R4(block, d, &e, a, b, &c,  3);
    R4(block, c, &d, e, a, &b,  4);
    R4(block, b, &c, d, e, &a,  5);
    R4(block, a, &b, c, d, &e,  6);
    R4(block, e, &a, b, c, &d,  7);
    R4(block, d, &e, a, b, &c,  8);
    R4(block, c, &d, e, a, &b,  9);
    R4(block, b, &c, d, e, &a, 10);
    R4(block, a, &b, c, d, &e, 11);
    R4(block, e, &a, b, c, &d, 12);
    R4(block, d, &e, a, b, &c, 13);
    R4(block, c, &d, e, a, &b, 14);
    R4(block, b, &c, d, e, &a, 15);

    /* Add the working vars back into digest[] */
    sha1->digest[0] += a;
    sha1->digest[1] += b;
    sha1->digest[2] += c;
    sha1->digest[3] += d;
    sha1->digest[4] += e;

    //for (int i = 0; i < 5; i++) {
    //    printf("%i", sha1->digest[i]);
   //     printf("\n");
   // }
   // printf("\n");
//
    /* Count the number of transformations */
    sha1->transforms++;
}

inline static void buffer_to_block(const char* buffer, unsigned __int32 block[BLOCK_INTS]) {
    /* Convert the const char* (byte buffer) to a unsigned __int32 array (MSB) */
    for (signed int i = 0; i < BLOCK_INTS; i++) {
        block[i] = (buffer[4*i+3] & 0xff)
            | (buffer[4*i+2] & 0xff) << 8
            | (buffer[4*i+1] & 0xff) << 16
            | (buffer[4*i+0] & 0xff) << 24;
    }
}

inline static void update(struct sha1* sha1, const char* str) {
    unsigned short position = 0;
    unsigned short size = fast_strlen(str);

    //printf("%llu", size); printf("\n");

    while (1) {
        if (position + BLOCK_BYTES > size) {
            sha1->buff_size = (unsigned __int32)(size - position);

            if (sha1->buff_size > 0) {
                //sha1->buffer = (char *) malloc(sizeof(char) * sha1->buff_size);
                sha1->buffer = (char *) malloc(sizeof(char) * BLOCK_BYTES);
                read_string(sha1->buffer, str + position, sha1->buff_size);
            }

            return;
        }
        else {
            sha1->buffer = (char *) malloc(sizeof(char) * BLOCK_BYTES);
            sha1->buff_size = BLOCK_BYTES;
            read_string(sha1->buffer, str + position, BLOCK_BYTES);
        }

        position += BLOCK_BYTES;

        //print_char_array(sha1->buffer, BLOCK_BYTES);

        unsigned __int32 block[BLOCK_INTS];
        buffer_to_block(sha1->buffer, block);
        transform(sha1, block);

        //for (int i = 0; i < 5; i++)
        //       printf("%u", sha1->digest[i]);
        //printf("\n\n");

        //realloc(sha1->buffer, BLOCK_BYTES + 1);
        //sha1->buffer[BLOCK_BYTES] = '\0';
        free(sha1->buffer);

        sha1->buffer = NULL;
        sha1->buff_size = 0;
    }
}

inline static void final(struct sha1* sha1, char* result) {
    /* Total number of hashed bits */
    unsigned __int64 total_bits = (sha1->transforms * BLOCK_BYTES + sha1->buff_size) * 8;
    // Padding
    unsigned __int32 orig_size = sha1->buff_size; // buff size is <= 63
    if (sha1->buffer) {
     //   realloc(sha1->buffer, BLOCK_BYTES); //orig_size + 1
    }
    else
        sha1->buffer = (char *) malloc(BLOCK_BYTES); // 1

    /*{
        sha1->buff_size++;
        orig_size++;
        sha1->buffer[0] = '1';
    }*/

    sha1->buffer[orig_size] = (char) 0x80;
    sha1->buff_size++;
    while (sha1->buff_size < BLOCK_BYTES) {
        sha1->buffer[sha1->buff_size] = (char) 0x00;
        sha1->buff_size++;
    }

    //printf("\n");
    //for (int i = 0; i < 64; i++) {
    ///    printf("%u", sha1->buffer[i]);
    //    printf("\n");
    //}
    //printf("\n\n");
    unsigned __int32 block[BLOCK_INTS];
    buffer_to_block(sha1->buffer, block);

    if (orig_size > BLOCK_BYTES - 8) {
        transform(sha1, block);
        for (size_t i = 0; i < BLOCK_INTS - 2; i++)
            block[i] = 0;
    }

    // Append total_bits, split this uint64_t into two uint32_t
    block[BLOCK_INTS - 1] = (unsigned __int32)total_bits;
    block[BLOCK_INTS - 2] = (unsigned __int32)(total_bits >> 32);
    transform(sha1, block);

    //for (int i = 0; i < 16; i++)
     //   printf("%u", block[i]);
    //printf("\n\n");

    unsigned int hex_count = sizeof(sha1->digest) / sizeof(sha1->digest[0]);
    //char* result = (char*)malloc(hex_count * 8 + 1);
    result[hex_count * 8] = '\0';

    //char* hex = (char*)malloc(8 * sizeof(char));
    char hex[8];

    for (int i = 0; i < hex_count; i++) {
        to_hex(hex, sha1->digest[i]);

        //printf("%u", sha1->digest[i]);
        //print_char_array(hex, 8);
        //printf("\n");

        result[0 + 8 * i] = hex[0];
        result[1 + 8 * i] = hex[1];
        result[2 + 8 * i] = hex[2];
        result[3 + 8 * i] = hex[3];

        result[4 + 8 * i] = hex[4];
        result[5 + 8 * i] = hex[5];
        result[6 + 8 * i] = hex[6];
        result[7 + 8 * i] = hex[7];
    }

    //return result;
    //return NULL;
}

#endif //COINMINER_SHA1_H
