//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Network.cpp
//

#pragma once

#include "Poll/Poll.hpp"
#include "Network/socket/Socket.hpp"
#include <memory>
#include <string>

namespace client {

/**
 * @class Network
 * @brief Handles client-server communication using sockets and polling.
 */
class Network {
   public:
    /**
     * @brief Constructs a Network object and establishes a connection to the server.
     * @param ip IP address of the server.
     * @param port Port number of the server.
     */
    Network(const std::string &ip, const std::string &port);

    /**
     * @brief Destroys the Network object and closes the connection.
     */
    ~Network();

    /**
     * @brief Sends a message/input to the server.
     * @param msg The message to send.
     */
    void sendInputToServer(const std::string &msg) const;

    /**
     * @brief Retrieves incoming data from the server and stores it internally.
     */
    void retrieveServerInformation();

    /**
     * @brief Gets the last command/data received from the server.
     * @return The latest server command or message.
     */
    std::string getCommand();

   private:
    std::unique_ptr<client::Socket> _socket; ///< Socket used for communication.
    std::unique_ptr<client::Poll> _poll; ///< Polling mechanism for non-blocking IO.
    std::string _cache; ///< Cache for received server messages.
};

}  // namespace client

