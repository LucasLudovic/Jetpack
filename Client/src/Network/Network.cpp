//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Network.cpp
//

#include "Network.hpp"
#include "Inputs/Inputs.hpp"
#include "Network/socket/Socket.hpp"
#include <memory>
#include <string>

client::Network::Network(const std::string &ip, const std::string &port)
    : _socket(std::make_unique<client::Socket>(ip, port))
{}

client::Network::~Network() {}

void client::Network::sendInputToServer(client::Inputs input) const
{
    this->_socket->sendInput(input);
}

std::string client::Network::retrieveServerInformation() const
{
    return this->_socket->getServerInformation();
}
