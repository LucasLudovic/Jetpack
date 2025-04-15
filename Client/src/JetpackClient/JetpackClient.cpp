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
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>

client::JetpackClient::JetpackClient(
    const std::string &ip, const std::string &port)
    : _ip(ip), _port(port), _running(true), _network(ip, port),
      _state(CLIENT_STATE::UNDEFIDED)
{}

client::JetpackClient::~JetpackClient() {}

std::uint8_t client::JetpackClient::runClient()
{
    this->_running = true;

    std::thread networkThread(&JetpackClient::runNetworkThread, this);
    std::thread displayThread(&JetpackClient::runDisplayThread, this);

    networkThread.join();
    displayThread.join();

    return RET_SUCCESS;
}
