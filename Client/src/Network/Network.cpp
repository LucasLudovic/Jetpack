//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Network.cpp
//

#include "Network.hpp"
#include "Network/socket/Socket.hpp"
#include "Poll/Poll.hpp"
#include <cstdlib>
#include <memory>
#include <string>
#include <sys/poll.h>
#include <sys/types.h>
#include <iostream>

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

std::string client::Network::getCommand()
{
    std::string command;
    size_t value = this->_cache.find("\r\n");
    std::cout << "cache = " << this->_cache << '\n';
    if (value == std::string::npos)
        return "";
    command = this->_cache.substr(0, value);
    this->_cache.erase(0, value + 2);
    std::cout << "NEW CMD\n";
    return command;
}

void client::Network::retrieveServerInformation()
{
    std::string msg;

    int rc = this->_poll->triggerPoll(33);
    if (rc > 0) {
        msg = this->_socket->getServerInformation();
    }
    this->_cache.append(msg);
}
