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

/**
 * @enum GameState
 * @brief Represents the different lifecycle states of the game server.
 *
 * @var GameState::WAITING_PLAYER
 *   Waiting for players to connect before initialization.
 * @var GameState::INIT
 *   Performing initialization (loading map, setting up game).
 * @var GameState::STARTED
 *   Game is actively running.
 * @var GameState::ENDED
 *   Game has finished and is awaiting shutdown.
 */
enum GameState {
    WAITING_PLAYER,
    INIT,
    STARTED,
    ENDED
};

/**
 * @struct server_s
 * @brief Core server context for the Jetpack Joyride multiplayer game.
 *
 * Contains configuration flags, sockets, game state, connected players,
 * and function pointers for all server operations.
 */
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

/**
 * @brief Allocate and initialize a new server.
 *
 * Sets up listening socket on @p port, loads the map file,
 * configures poll descriptors, and assigns virtual methods.
 *
 * @param port   TCP port number to listen on.
 * @param map    Path to map file.
 * @param debug  Debug flag (non-zero to enable debug mode).
 * @return Pointer to initialized server_t, or NULL on error.
 */
server_t *create_server(int port, const char *map, int debug);

/**
 * @brief Run the server's main loop.
 *
 * Enters polling loop, accepts new connections,
 * handles input, updates game state, and sends updates.
 *
 * @param this Pointer to server instance.
 * @return Zero on clean shutdown, non-zero on error.
 */
int run_server(struct server_s *this);

/**
 * @brief Send full map data to all connected players.
 *
 * Iterates over server->players and transmits the map contents.
 *
 * @param server Server instance.
 */
void send_map(server_t *server);

/**
 * @brief Log debug information on socket.
 *
 * If @p is_send is true, writes @p data as send data; otherwise,
 * write them as received data
 *
 * @param server  Server context.
 * @param data    Debug message text.
 * @param is_send Is the data received or send.
 */
void debug(server_t *server, const char *data, int is_send);

#endif /* ifndef SERVER_H_ */
