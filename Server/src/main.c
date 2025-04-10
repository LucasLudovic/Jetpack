/*
** EPITECH PROJECT, 2025
** Main
** File description:
** Main
*/

#include "app.h"
#include "my_macros.h"
#include <stdio.h>

int display_help(void)
{
    printf(
        "./jetpack_server -p <port> -m <map> [-d]"
        "p is the port on which to listen, m is the path to the map file and "
        "the optional d is for enabling debug mode");
    return EPITECH_FAILURE;
}

int main(int argc, char **argv)
{
    if (argc < 5 || argc > 6 || argv == NULL || argv[1] == NULL ||
        argv[2] == NULL || argv[3] == NULL || argv[4] == NULL) {
        return display_help();
    }
    if (run_app(argv[2], argv[4], argv[5]) != SUCCESS)
        return EPITECH_FAILURE;
    return EPITECH_SUCCESS;
}
