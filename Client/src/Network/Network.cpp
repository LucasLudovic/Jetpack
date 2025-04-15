//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Network.cpp
//

#include "Network.hpp"
#include "Inputs/Inputs.hpp"
#include "Network/socket/Socket.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <sys/poll.h>

client::Network::Network(const std::string &ip, const std::string &port)
{
    this->_socket = std::make_unique<client::Socket>(ip, port);
    this->_socket->createConnection();
}

client::Network::~Network() {}

void client::Network::sendInputToServer(const std::string &msg) const
{
    this->_socket->sendInput(msg);
}

std::string client::Network::retrieveServerInformation() const
{
    struct pollfd *pfds = (struct pollfd *)malloc(sizeof(struct pollfd));
    pfds[0].fd = this->_socket->getSocket();
    pfds[0].events = POLLIN;
    int rc = poll(pfds, 1, 33);
    if (rc > 0) {
        std::string msg = this->_socket->getServerInformation();
    }
    this->sendInputToServer(ok);
    return msg;
}
