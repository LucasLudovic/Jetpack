//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Socket.hpp
//

#pragma once

#include "Inputs/Inputs.hpp"
#include <exception>
#include <memory>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>

namespace client {
    class Socket {
       public:
        class SocketError : public std::exception {
           public:
            SocketError() { this->_msg = "Socket Error"; }

            const char *what() const noexcept override
            {
                return this->_msg.c_str();
            }

           private:
            std::string _msg;
        };

        Socket(const std::string &ip, const std::string &port);
        ~Socket();

        void createConnection();
        void sendInput(client::Inputs input) const;
        const std::string &getServerInformation() const;

       private:
        int _socket;
        int _port;
        socklen_t _addrlen;
        std::unique_ptr<struct sockaddr_in> _address;
    };
}  // namespace client
