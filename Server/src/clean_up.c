/*
** EPITECH PROJECT, 2025
** cleanup
** File description:
** Free functions
*/

#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void simple_free(void **ptr)
{
    if (!ptr || !*ptr) {
        return;
    }
    free(*ptr);
    *ptr = NULL;
}

void free_server(server_t **server)
{
    if (!server) {
        return;
    }
    printf("Server Cleanup\n");
    if ((*server)->socket > 0) {
        close((*server)->socket);
    }
}
