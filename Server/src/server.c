/*
** EPITECH PROJECT, 2025
** server
** File description:
** server
*/

#include "server.h"
#include "cleanup.h"
#include "my_macros.h"
#include <stdio.h>
#include <stdlib.h>

server_t *create_server(void)
{
    server_t *server = malloc(sizeof(server_t));

    if (!server) {
        fprintf(stdout, "Alloc failed for server");
        return NULL;
    }
    server->init;
    server->run();
}

int run_app(char *map)
{
    server_t AUTOFREE_SERVER *server = create_server();

    if (server->init() == FAILURE)
        return FAILURE;
}
