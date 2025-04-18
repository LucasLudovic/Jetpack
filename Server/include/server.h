/*
** EPITECH PROJECT, 2025
** server
** File description:
** Server struct with basic functions
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include "map.h"
    #include "player.h"
    #include <stddef.h>
    #include <unistd.h>

    #define NB_PLAYER_MAX 2

enum GameState {
    WAITING_PLAYER,
    INIT,
    STARTED,
    ENDED
};

typedef struct server_s {
    int is_debug;
    int is_running;
    int map_sent;
    char *map_file;
    char *map[MAP_HEIGHT];
    enum GameState game_state;

    struct pollfd *socket;
    struct sockaddr_in *address;
    int port;
    socklen_t socklen;

    size_t nb_player;
    player_t *players[NB_PLAYER_MAX];

    int (*run)(struct server_s *this);
    void (*destroy)(struct server_s **this);
    void (*send)(player_t *player, const char *msg);
    void (*send_map)(struct server_s *server);
    void (*remove_player)(struct server_s *server, size_t i);
    void (*init_game)(struct server_s *server);
    void (*start_game)(struct server_s *server);
    void (*load_map)(struct server_s *server);
} server_t;

server_t *create_server(int port, const char *map, int debug);
int run_server(struct server_s *this);
void send_map(server_t *server);

#endif /* ifndef SERVER_H_ */
