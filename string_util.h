//
// Created by Nikita on 05.02.2021.
//

#ifndef COINMINER_STRING_UTIL_H
#define COINMINER_STRING_UTIL_H

inline static void print_char_array(const char* str, unsigned __int32 count) {
    while (count) {
        printf("%c", *str);
        str++;
        count--;
    }

    /*char* arr = (char*)malloc(count + 1);
    arr[count] = '\0';
    unsigned __int32 it = 0;
    while(count) {
        arr[it] = *str;
        str++;
        it++;
        count--;
    }
    printf("%s", arr);
    free(arr);*/
}

inline char to16(unsigned char number) {
    switch (number) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        case 10: return 'a';
        case 11: return 'b';
        case 12: return 'c';
        case 13: return 'd';
        case 14: return 'e';
        case 15: return 'f';
    }
}

void to_hex(char* hex, unsigned __int32 num) {
    hex[7] = to16(num % 16); num /= 16;
    hex[6] = to16(num % 16); num /= 16;
    hex[5] = to16(num % 16); num /= 16;
    hex[4] = to16(num % 16); num /= 16;

    hex[3] = to16(num % 16); num /= 16;
    hex[2] = to16(num % 16); num /= 16;
    hex[1] = to16(num % 16); num /= 16;
    hex[0] = to16(num % 16);
}

inline static __int64 fast_strlen(const char* str) {

    unsigned __int64 size = 0;
    while(*str) {
        size++;
        str++;
    }
    return size;
}

inline static void read_string(char* out, const char* source, unsigned __int32 count) {
    while(count) {
        *out = *source;
        out++;
        source++;
        count--;
    }
}

inline static void append(char* str, char symbol, unsigned char size, unsigned char count) {
   //realloc(str, size + count);
    /*str += size;
    while (count) {
        *str = symbol;
        str++;
        count--;
    }*/

}

#endif //COINMINER_STRING_UTIL_H
