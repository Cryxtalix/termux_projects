#ifndef CURL_URL_H
#define CURL_URL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

/**
 * @brief Returns result from API url
 * 
 * @param url 
 * @return char*
 */
char * api_call(char *url);

#endif //CURL_URL_H