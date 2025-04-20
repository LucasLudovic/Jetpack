/*
** EPITECH PROJECT, 2025
** App
** File description:
** App
*/

#ifndef APP_H_
    #define APP_H_

/**
 * @brief Main server application entry point.
 *
 * Initializes and runs the game server on the specified port,
 * loading the given map file, and optionally enabling debug mode.
 *
 * @param port  Port number as C-string on which to listen.
 * @param map   Path to the map file to load.
 * @param debug If non-null and enable debug logging.
 * @return Zero on clean exit, non-zero on error.
 */
int run_app(const char *port, const char *map, const char *debug);

#endif
