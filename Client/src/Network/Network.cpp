//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Network.cpp
//

#include "Network.hpp"
#include "Inputs/Inputs.hpp"
#include "JetpackClient/Poll/Poll.hpp"
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

    this->_poll = std::make_unique<client::Poll>(this->_socket->getSocket());
}

client::Network::~Network() {}

void client::Network::sendInputToServer(const std::string &msg) const
{
    this->_socket->sendInput(msg);
}

std::string client::Network::retrieveServerInformation() const
{
    std::string msg;

    int rc = this->_poll->triggerPoll(33);
    if (rc > 0) {
        msg = this->_socket->getServerInformation();
    }
    return msg;
}
