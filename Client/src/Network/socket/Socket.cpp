//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Socket.cpp
//

#include "Socket.hpp"
#include "Inputs/Inputs.hpp"
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

client::Socket::Socket(const std::string &ip, const std::string &port)
{
    this->_socket = socket(AF_INET, SOCK_STREAM, 0);
    this->_address = std::make_unique<sockaddr_in>();
    this->_address->sin_family = AF_INET;
    this->_address->sin_port = htons(atoi(port.c_str()));
    this->_address->sin_addr.s_addr = inet_addr(ip.c_str());
    this->_addrlen = sizeof(*this->_address);
}

client::Socket::~Socket() {}

void client::Socket::createConnection()
{
    if (connect(this->_socket,
            reinterpret_cast<sockaddr *>(this->_address.get()),
            this->_addrlen) == -1) {
        throw SocketError("Connect Failed");
    }
}

void client::Socket::sendInput(const std::string &msg) const
{
    std::string messageFormat = msg + "\r\n";
    if (send(this->_socket, messageFormat.c_str(), strlen(messageFormat.c_str()), 0) == -1) {
        throw SocketError("Send Failed");
    }
}

std::string client::Socket::getServerInformation() const
{
    char buf[256];
    std::string str;
    ssize_t bytes_read = 0;

    while (true) {
        bytes_read = read(this->_socket, buf, sizeof(buf));
        if (bytes_read < 0)
            break;
        if (bytes_read == 0) {
            close(this->_socket);
            break;
        }
        str.append(buf, bytes_read);
        if (bytes_read < 256)
            break;
    }
    return str;
}
