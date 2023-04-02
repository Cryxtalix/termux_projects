#ifndef TERMUX_OUT_H
#define TERMUX_OUT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Outputs a single string to termux-notification via termux:API
 * 
 * @param text 
 */
void notif_print(char *text, char *title);

/**
 * @brief Outputs a single string to termux-toast via termux:API
 * 
 * @param text 
 */
void toast_print(char *text);

#endif //TERMUX_OUT_H