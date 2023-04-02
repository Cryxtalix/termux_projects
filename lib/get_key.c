#include "get_key.h"

char name_buffer[255];
char key[255];

char * get_key(char *token_name)
{
    char buffer[255];
    char **tokens = malloc(sizeof(char *));

    FILE *fp;
    fp = fopen(".env", "r");

    // Get lines with fgets
    int no_of_tok = 0;
    while (fgets(buffer, 254, fp) != NULL) {
        if (strlen(buffer) > 1) { // Avoid blank lines
            tokens[no_of_tok] = malloc(255 * sizeof(char));
            strncpy(tokens[no_of_tok], buffer, 254);
            no_of_tok++;
        }
    }

    fclose(fp);

    // Find the token I want
    for (int i = 0; i < no_of_tok; i++) {
        memset(name_buffer, 0, strlen(name_buffer));
        memset(key, 0, strlen(key));
        int eq_pos = -1;

        for (int j = 0; j < strlen(tokens[i]); j++) {
            if (tokens[i][j] == '\n') {
                continue;
            }
            if (tokens[i][j] == '=') { // Find equals sign
                eq_pos = j;
            }
            if (eq_pos == -1) {
                char temp_str[2];
                temp_str[0] = tokens[i][j];
                temp_str[1] = '\0';
                strncat(name_buffer, temp_str, 1);
            }
            if (j > eq_pos && eq_pos != -1) {
                char temp_str[2];
                temp_str[0] = tokens[i][j];
                temp_str[1] = '\0';
                strncat(key, temp_str, 1);
            }
        }

        if (strcmp(name_buffer, token_name) == 0) {
            free(tokens);
            return key;
        }
    }

    free(tokens);
    return "";
}