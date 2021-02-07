#include <stdio.h>
#include <time.h>
#include <malloc.h>

#include "https_util.h"
#include "unit_test.h"

#pragma comment(lib,"Ws2_32.lib")

#include <string.h>

#include <winsock2.h>
#include <ws2tcpip.h>

_Bool request_job(SOCKET sock) {
    const char* req = "JOB,Monika";
    if(send(sock, req, fast_strlen(req), 0) < 0) {
        printf("request_job() : failed\n");
        return 0;
    } else return 1;
}

SOCKET connect_to_server(char* ip, unsigned short port) {
    printf("%s", ip); printf(":"); printf("%hu", port); printf("\n");

    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char server_reply[4];

    printf("connect_to_server(): initializing socket...\n");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0) {
        printf("connect_to_server(): failed. Error Code : %d",WSAGetLastError());
        return 0;
    }

    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET) {
        printf("connect_to_server(): Could not create socket : %d" , WSAGetLastError());
        return INVALID_SOCKET;
    }

    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    //Connect to remote server
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0) {
        printf("connect_to_server(): connect error\n");
        return 0;
    }

    printf("connect_to_server(): successfully connection!\n");

    //Receive a reply from the server
    if((recv(s , server_reply , 3 , 0)) == SOCKET_ERROR) {
        printf("connect_to_server(): recv version failed\n");
        return 0;
    }

    server_reply[3] = '\0';

    printf("connect_to_server(): server version: "); printf("%s", server_reply); printf("\n");

    return s;
}

void process_job(SOCKET sock, struct sha1* sha1, struct sha1* sha1_copy) {
    char buffer[100];
    int size = recv(sock, buffer, 100, 0);
    buffer[size] = '\0';

    unsigned short id = 0;
    char* prefix = read_to(buffer, ',', &id);
    char* job = read_to(buffer + id, ',', &id);
    unsigned int diff = (unsigned int)atoi(buffer + id);

    printf("%s\n", prefix);
    printf("%s\n", job);
    printf("%i\n", diff);

    char iter_hash [32];
    char final_hash[65];

    //update(sha1, prefix);
    for (unsigned int i = 0; i < diff * 100; i++) {
        //update(sha1, prefix);

        itoa((int)i, iter_hash, 10);
        char buffer[100];
        strcpy(buffer, prefix);
        strcat(buffer, iter_hash);

        update(sha1, buffer);
        final(sha1, final_hash);

        //if (string_compare(job, final_hash)){
        if (strcmp(job, final_hash) == 0) {
            printf("%s\n", final_hash);
            printf("%i\n", i);
            break;
        }

        reset(sha1);
    }
}

void test_speed(){
    unsigned int i = 0;
    clock_t _time = clock();

    for (unsigned int it = 0; it < 10000000; it++)
        i = atoi("4234324");

    printf("Time: %ld\n",
           (clock() - _time) / 1000);
    _time = clock();

    for (unsigned int it = 0; it < 10000000; it++)
        i = str_to_uint("4234324");

    printf("Time: %ld\n",
           (clock() - _time) / 1000);

    printf("%u", i);
}

int main() {
    curl_global_init(CURL_GLOBAL_ALL); //CURL_GLOBAL_ALL CURL_GLOBAL_DEFAULT

    if (!check_sha1() || !check_sha1_2() || !check_sha1_3()) {
        printf("SHA1 is not working!\n");
        return -1;
    } else
        printf("Checking SHA1 is successful\n");

    char *ip = NULL;
    unsigned short port = 0;
    get_address("https://raw.githubusercontent.com/revoxhere/duino-coin/gh-pages/serverip.txt", &ip, &port);

    SOCKET sock = connect_to_server(ip, port);
    if (sock == INVALID_SOCKET)
        return -1;

    struct sha1* sha1 = newSHA1();

    struct sha1* sha1_copy = newSHA1();
    sha1_copy->buffer = (char*)malloc(BLOCK_BYTES + 1);
    sha1_copy->buffer[BLOCK_BYTES] = '\0';

    //while(1)
        if (request_job(sock)) {
            process_job(sock, sha1, sha1_copy);
            reset(sha1);
            return 0;
        }

    return -1;


    /*const char* input = "[11111111111111111111111111111111111111111111111111111111111111]\0";



    char* hash = (char*)malloc(BLOCK_BYTES + 1);

    clock_t _time = clock();

    for (unsigned int i = 0; i < 10000000; i++) {
        update(checksum, input);

        final(checksum, hash);

        //printf("%s", hash); printf("\n");

        reset(checksum);
    }

    printf("Time: %ld\n",
           (clock() - _time) / 1000);

    free(hash);
    free(checksum);*/

    return 0;
}
