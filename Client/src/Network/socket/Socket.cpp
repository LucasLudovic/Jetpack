//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Socket.cpp
//

#include "Socket.hpp"
#include <arpa/inet.h>
#include <cstdlib>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>

client::Socket::Socket(const std::string &ip, const std::string &port)
{
    this->_socket = socket(AF_INET, SOCK_STREAM, 0);
    this->_address->sin_family = AF_INET;
    this->_address->sin_port = htons(atoi(port.c_str()));
    this->_address->sin_addr.s_addr = inet_addr(ip.c_str());
    this->_addrlen = sizeof(*this->_address);
}

client::Socket::~Socket() {}

void client::Socket::createConnection()
{
    if (connect(this->_socket, reinterpret_cast<sockaddr *>(this->_address.get()), this->_addrlen) == -1) {
        throw SocketError();
    }
}
