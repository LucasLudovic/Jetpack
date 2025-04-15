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
#include <cstring>
#include <iostream>
#include <string>
#include <thread>

client::JetpackClient::JetpackClient(
    const std::string &ip, const std::string &port)
    : _ip(ip), _port(port), _running(true), _network(ip, port),
      _state(CLIENT_STATE::UNDEFIDED)
{}

client::JetpackClient::~JetpackClient() {}

void client::JetpackClient::setupGame()
{
    auto cmd = this->_network.retrieveServerInformation();
    if (cmd == "WAITING_PLAYERS\r\n") {
        this->_state = CLIENT_STATE::WAITING;
    } else {
        throw ClientError(
            "Server must send Waiting players like first message");
    }
    auto isMap = this->_network.retrieveServerInformation();
    if (isMap == "SEND_MAP\r\n") {
        // retrieve map
    }
}

std::uint8_t client::JetpackClient::runClient()
{
    this->_running = true;

    this->setupGame();

    std::thread networkThread(&JetpackClient::runNetworkThread, this);
    std::thread displayThread(&JetpackClient::runDisplayThread, this);

    networkThread.join();
    displayThread.join();

    return RET_SUCCESS;
}
