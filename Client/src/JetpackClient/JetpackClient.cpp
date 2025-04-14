//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// JetpackClient.cpp
//

#include "JetpackClient.hpp"
#include "Network/Network.hpp"
#include "client.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#include <thread>

client::JetpackClient::JetpackClient(
    const std::string &ip, const std::string &port)
    : _ip(ip), _port(port)
{}

client::JetpackClient::~JetpackClient() {}

std::uint8_t client::JetpackClient::runClient()
{
    client::Network network(this->_ip, this->_port);
    return RET_SUCCESS;
}
