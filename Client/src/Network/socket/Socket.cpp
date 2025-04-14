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
#include <memory>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <iostream>

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
    if (connect(this->_socket, reinterpret_cast<sockaddr *>(this->_address.get()), this->_addrlen) == -1) {
        throw SocketError("Connect Failed");
    }
}

void client::Socket::sendInput(client::Inputs input) const
{
    if (input.state == ev_state::PRESSED)
        if (send(this->_socket, "PRESS\r\n", 7, 0) == -1) {
            throw SocketError("Send Failed");
        }
}


std::string client::Socket::getServerInformation() const 
{
    char buf[256];

    if (recv(this->_socket, buf, 256, 0) == -1)
        throw SocketError("Recv Failed");
    return buf;
}
