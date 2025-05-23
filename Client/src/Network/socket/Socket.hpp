//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Socket.hpp
//

#pragma once

#include <exception>
#include <memory>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>

namespace client {

/**
 * @class Socket
 * @brief Handles low-level socket communication with the server.
 */
class Socket {
   public:
    /**
     * @class SocketError
     * @brief Exception class for socket-related errors.
     */
    class SocketError : public std::exception {
       public:
        /**
         * @brief Constructs a new SocketError with a message.
         * @param msg The error message.
         */
        SocketError(const std::string &msg) { this->_msg = msg; }

        /**
         * @brief Returns the error message.
         * @return A C-string describing the error.
         */
        const char *what() const noexcept override
        {
            return this->_msg.c_str();
        }

       private:
        std::string _msg; ///< Error message.
    };

    /**
     * @brief Constructs a new Socket object.
     * @param ip The server IP address.
     * @param port The server port number.
     */
    Socket(const std::string &ip, const std::string &port);

    /**
     * @brief Destroys the Socket object and closes the connection if open.
     */
    ~Socket();

    /**
     * @brief Creates the connection to the server.
     */
    void createConnection();

    /**
     * @brief Sends a message to the server.
     * @param msg The message to send.
     */
    void sendInput(const std::string &msg) const;

    /**
     * @brief Receives information from the server.
     * @return The received string.
     */
    [[nodiscard]] std::string getServerInformation() const;

    /**
     * @brief Returns the raw socket file descriptor.
     * @return The socket descriptor as an integer.
     */
    int getSocket() const;

   private:
    int _socket; ///< File descriptor for the socket.
    int _port; ///< Port number.
    socklen_t _addrlen; ///< Length of the socket address.
    std::unique_ptr<struct sockaddr_in> _address; ///< Address structure for the socket.
};

}  // namespace client

