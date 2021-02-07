//
// Created by Nikita on 05.02.2021.
//

#ifndef COINMINER_STRING_UTIL_H
#define COINMINER_STRING_UTIL_H
#include <math.h>

inline static void print_char_array(const char* str, unsigned __int32 count) {
    while (count) {
        printf("%c", *str);
        str++;
        count--;
    }
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

//void read_to(char* out, const char* source, )

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

inline static short fast_strlen(const char* str) {
    unsigned short size = 0;
    while(*str) {
        size++;
        str++;
    }
    return size;
}

inline static _Bool string_compare(const char* str1, const char* str2) {
    unsigned short size1 = fast_strlen(str1);
    unsigned short size2 = fast_strlen(str2);
    if (size1 != size2)
        return 0;
    else{
        while (size1){
            if (*str1 != *str2)
                return 0;
            str1++;
            str2++;
            size1--;
        }
        return 1;
    }
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

inline static unsigned char char_to_number(char c){
    switch (c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        default: return -1;
    }
}

inline static unsigned int str_to_uint(const char* str) {
    unsigned short size = fast_strlen(str);
    unsigned int result = 0;
    for (unsigned short i = 0; i < size; i++)
        result += char_to_number(str[i]) * (pow(10, size - i - 1));
    return result;
}

inline static unsigned short str_to_ushort(const char* str) {
    unsigned char size = fast_strlen(str);
    unsigned short result = 0;
    for (unsigned char i = 0; i < size; i++)
        result += char_to_number(str[i]) * (pow(10, size - i - 1));
    return result;
}

inline static char* read_to(const char* str, char symbol, unsigned short* id) {
    unsigned short size = fast_strlen(str);
    for (unsigned short i = 0; i < size; i++) {
        if (str[i] == symbol){
            char* result = (char*)malloc((i + 1) * sizeof(char));
            read_string(result, str, i);
            result[i] = '\0';
            (*id) += i + 1;
            return result;
        }
    }
    return NULL;
}


#endif //COINMINER_STRING_UTIL_H
