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
    if (argc < 5 || argc > 6) {
        return display_help();
    }
    return run_app(argv[1]);
}
