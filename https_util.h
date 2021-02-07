//
// Created by Monika on 07.02.2021.
//

#include <malloc.h>
#include <curl/curl.h>
#include "string_util.h"

#ifndef COINMINER_HTTPS_UTIL_H
#define COINMINER_HTTPS_UTIL_H

static char* g_userdata;

inline size_t write_callback(char *data, size_t size, size_t nmemb, void *userdata) {
    size_t realsize = size * nmemb;

    g_userdata = (char*)malloc(realsize);
    memcpy(g_userdata, data, realsize);

    return realsize;
}

void get_address(const char* url, char** ip, unsigned short* port) {
    CURL *handle = curl_easy_init();
    CURLcode res;

    if(handle) {
        curl_easy_setopt(handle, CURLOPT_URL, url);
        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback);

        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);

        res = curl_easy_perform(handle);
        if (res != CURLE_OK) {
            printf("get_address(): failed perform! Reason: ");
            printf("%s", curl_easy_strerror(res));
        }else{
            //printf("%s", g_userdata);

            unsigned short id = 0;
            *ip = read_to(g_userdata, '\n', &id);
            *port = (unsigned short)atoi(read_to(g_userdata + id, '\n', &id));

            //printf("%s", ip);
            //printf(":");
            //printf("%hu", *port);
        }

        curl_easy_cleanup(handle);
    } else
        printf("get_address(): failed init curl!\n");
}

#endif //COINMINER_HTTPS_UTIL_H
