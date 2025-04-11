/*
** EPITECH PROJECT, 2025
** Server run
** File description:
** Main loop of the server struct
*/

#include "cleanup.h"
#include "my_macros.h"
#include "server.h"
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>

static void accept_connection(server_t *server)
{
    struct pollfd *pfds = NULL;
    const char *msg = "220 Connection established.\r\n";

    pfds = malloc(sizeof(struct pollfd));
    if (!pfds) {
        fprintf(stderr, "Unable to alloc pollfd\n");
        free_server(server);
        exit(EPITECH_FAILURE);
    }
    pfds->fd = accept(server->socket->fd,
        (struct sockaddr *)server->address, &server->socklen);
    if (pfds->fd < 0) {
        free(pfds);
        fprintf(stderr, "Unable to accept connection\n");
        return;
    }
    pfds->events = POLLIN;
    server->players[server->nb_player] = create_player(pfds);
    server->nb_player += 1;
    if (server->players[server->nb_player - 1] == NULL) {
        fprintf(stderr, "Unable to create player");
        free_server(&server);
        exit(EPITECH_FAILURE);
    }
    write(pfds->fd, msg, strlen(msg));
}

static int check_remove_socket(
    server_t *server, size_t i)
{
    if (server->players[i]->socket->revents & POLLHUP ||
        server->players[i]->socket->revents & POLLERR) {
        if (i == 0) {
            free_server(&server);
            fprintf(stderr, "Error on server socker\n");
            exit(EPITECH_FAILURE);
        }
        free_player(&(server->players[i]));
        return TRUE;
    }
    return FALSE;
}

static void check_pfds(server_t *server, struct pollfd *clients_pfds, size_t i)
{
    if (check_remove_socket(server, i))
        return;
    if (clients_pfds[i].revents & POLLIN) {
        if (i == 0) {
            accept_connection(server);
            return;
        }
        execute_instructions(server, &clients_pfds[i], i - 1);
    }
}

static void loop_poll(
    struct pollfd *clients_pfds, server_t *server, size_t nb_clients)
{
    signal(SIGPIPE, SIG_IGN);
    for (size_t i = 0; i < nb_clients + 1; i += 1) {
        check_pfds(server, clients_pfds, i);
    }
}

static void loop_server(server_t *server)
{
    int ret = 0;
    size_t nb_clients = 0;
    struct pollfd *clients_pfds = NULL;

    // clients_pfds = get_pfds_from_clients(server);
    nb_clients = server->nb_player;
    ret = poll(clients_pfds, nb_clients + 1, -1);
    if (ret > 0) {
        loop_poll(clients_pfds, server, nb_clients);
    }
    free(clients_pfds);
}

int run_server(server_t *this)
{
    while (this->is_running) {}
    return SUCCESS;
}
