#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lib/curl_url.h"
#include "./lib/jsmn.h"
#include "./lib/termux_output.h"

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

int main(int argc, char **argv)
{
    //{"179", "27329"};
    //{"241", "27309"};
    
    if (argc < 3 || (argc % 2) != 1) {
        toast_print("Please enter a valid input pairs");
        return EXIT_FAILURE;
    }

    int query_num = (argc - 1) / 2;

    for (int i = 1; i < query_num+1; i++)
    {
        char url[50] = "https://arrivelah2.busrouter.sg/?id=";
        char *input1 = argv[(i*2) - 1];
        char *input2 = argv[i*2];
        char **bus_num;

        if (strlen(input1) != 5 && strlen(input2) != 5 || 
            strlen(input1) == 5 && strlen(input2) == 5) {
            toast_print("Please enter a valid input pairs");
            continue;
        }

        if (strlen(input1) == 5) {
            strncat(url, input1, 50 - strlen(url));
            bus_num = &input2;
        } else {
            strncat(url, input2, 50 - strlen(url));
            bus_num = &input1;
        }

        char *json_out = api_call(url);

        //Parse JSON
        jsmn_parser p;
        jsmntok_t t[1024];
        jsmn_init(&p);

        int r = jsmn_parse(&p, json_out, strlen(json_out), t, sizeof(t) / sizeof(t[0]));

        if (r < 0) {
            fprintf(stderr, "Failed to parse JSON: %d\n", r);
            return EXIT_FAILURE;
        }

        for (int i = 0; i < r; i++) {
            if (jsoneq(json_out, &t[i], "services") == 0) {
                printf("%.*s\n", t[i + 1].end - t[i + 1].start, json_out + t[i + 1].start);
            }
        }
    }

    return EXIT_SUCCESS;
}
