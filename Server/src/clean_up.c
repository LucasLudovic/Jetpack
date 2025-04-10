/*
** EPITECH PROJECT, 2025
** cleanup
** File description:
** Free functions
*/

#include "server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
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
    if (!server || !(*server)) {
        return;
    }
    if ((*server)->is_debug) {
        printf("Server Cleanup\n");
    }
    if ((*server)->map_file) {
        free((*server)->map_file);
    }
    if ((*server)->socket) {
        if ((*server)->socket->fd >= 0) {
            close((*server)->socket->fd);
        }
        free((*server)->socket);
    }
    if ((*server)->address) {
        free((*server)->address);
    }
    free(*server);
}
