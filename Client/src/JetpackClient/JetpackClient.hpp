//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// JetpackClient.hpp
//

#pragma once

#include "Display/Display.hpp"
#include "Network/Network.hpp"
#include "Player/Player.hpp"
#include <cstdint>
#include <mutex>
#include <queue>
#include <string>
#include <vector>

namespace client {

/**
 * @enum CLIENT_STATE
 * @brief Represents the current state of the client.
 */
enum class CLIENT_STATE : std::uint8_t {
    UNDEFIDED, ///< State is undefined.
    PLAYING,   ///< Client is actively playing.
    WAITING    ///< Client is waiting for another player or event.
};

/**
 * @class JetpackClient
 * @brief Main client class that manages network communication, display, and game state.
 */
class JetpackClient {
   public:
    /**
     * @class ClientError
     * @brief Exception class for client-related errors.
     */
    class ClientError : public std::exception {
       public:
        /**
         * @brief Constructs a ClientError with the given message.
         * @param msg The error message.
         */
        ClientError(const std::string &msg) { this->_msg = msg; }

        /**
         * @brief Returns the error message.
         * @return A C-style string containing the error message.
         */
        const char *what() const noexcept override
        {
            return this->_msg.c_str();
        }

       private:
        std::string _msg; ///< The error message.
    };

    /**
     * @brief Constructs a JetpackClient object and connects to the server.
     * @param ip IP address of the server.
     * @param port Port number of the server.
     * @param debugMode Enable or disable debug mode.
     */
    JetpackClient(const std::string &ip, const std::string &port, bool debugMode);

    /**
     * @brief Destroys the JetpackClient and cleans up resources.
     */
    ~JetpackClient();

    /**
     * @brief Starts the client loop.
     * @return Exit status code.
     */
    std::uint8_t runClient();

   private:
    std::string _ip; ///< Server IP address.
    std::string _port; ///< Server port.
    bool _debugMode; ///< Whether debug mode is enabled.
    bool _running; ///< Whether the client is currently running.
    CLIENT_STATE _state; ///< Current state of the client.

    std::queue<std::string> _data; ///< Queue of data received from the server.
    std::queue<std::string> _msg; ///< Queue of messages to send to the server.
    std::mutex data_mutex; ///< Mutex for thread-safe access to data queues.

    client::Network _network; ///< Handles networking.
    client::Display _displayEngine; ///< Handles display/rendering.
    Player _player; ///< Local player.
    Player _player2; ///< Opponent player.

    bool _MapIsRetrieve; ///< Whether the map has been retrieved from the server.
    std::vector<std::string> _map; ///< Current game map.

    /**
     * @brief Handles the network thread (receiving data, etc.).
     */
    void _runNetworkThread();

    /**
     * @brief Handles the display thread (rendering, events).
     */
    void _runDisplayThread();

    /**
     * @brief Retrieves and processes data from the server.
     */
    void _retrieveDataServer();

    /**
     * @brief Handles the game display logic.
     */
    void _handleDisplay();

    /**
     * @brief Handles the game logic while running.
     * @param currentData The current game data received from server.
     */
    void _gameRunning(const std::string &currentData);

    /**
     * @brief Sends queued messages to the server.
     */
    void _sendMessage();

    /**
     * @brief Handles waiting state when waiting for players.
     */
    void _handleWaitingPlayers();

    /**
     * @brief Starts the game map.
     */
    void _startMap();

    /**
     * @brief Loads the map received from the server.
     * @param map The map data as a string.
     */
    void _retrieveMap(const std::string &map);

    /**
     * @brief Ends the current map session.
     */
    void _endMap();

    /**
     * @brief Starts the game as player one.
     */
    void _startGamePlayerOne();

    /**
     * @brief Starts the game as player two.
     */
    void _startGamePlayerTwo();

    /**
     * @brief Updates the player's position based on received data.
     * @param pos Player position data as a string.
     */
    void _updatePlayerPosition(const std::string &pos);

    /**
     * @brief Retrieves coin data from the server and updates the game state.
     */
    void _retrieveCoin();
};

}  // namespace client

