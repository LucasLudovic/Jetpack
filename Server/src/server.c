/*
** EPITECH PROJECT, 2025
** server
** File description:
** server
*/

#include "server.h"
#include "cleanup.h"
#include "my_macros.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>

int run_app(const char *port, const char *map, const char *debug)
{
    server_t AUTOFREE_SERVER *server = NULL;
    int portNumber = 0;
    int isDebug = TRUE;

    if (port == NULL || map == NULL) {
        fprintf(stderr, "Wrong parameters to init server");
        return FAILURE;
    }
    portNumber = atoi(port);
    if (debug == NULL || strcmp(debug, "-d") != 0) {
        isDebug = FALSE;
    }
    server = create_server(portNumber, map, isDebug);
    if (server == NULL) {
        return FAILURE;
    }
    server->run(server);
    return SUCCESS;
}
