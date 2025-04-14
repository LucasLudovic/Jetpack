//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Network.cpp
//

#include "Network.hpp"
#include "Inputs/Inputs.hpp"
#include "Network/socket/Socket.hpp"
#include <iostream>
#include <memory>
#include <string>

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
    return this->_socket->getServerInformation();
}
