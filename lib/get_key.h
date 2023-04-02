#ifndef GET_KEY_H
#define GET_KEY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Returns specified key from .env file
 * 
 * @param token_name 
 * @return char* 
 */
char * get_key(char *token_name);

#endif //GET_KEY_H