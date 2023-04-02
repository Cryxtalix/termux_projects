#include "curl_url.h"

char json_out[10000];

size_t save_data(char *buffer, size_t itemsize, size_t nmemb, void *userdata) {
    size_t bytes = itemsize * nmemb;

    for (int i = 0; i < bytes; i++) {
        strncat(json_out, &buffer[i], 1);
    }
    return bytes;
}

char * api_call(char *url)
{
    // CURL
    CURL *curl = curl_easy_init();

    if(!curl) {
        fprintf(stderr, "Init failed\n");
        return "ERROR";
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, save_data);
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "Request failed: %s/n", curl_easy_strerror(res));
    }
    curl_easy_cleanup(curl);

    return json_out;
}
