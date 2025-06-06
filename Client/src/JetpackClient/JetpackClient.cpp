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
#include <string>
#include <thread>

client::JetpackClient::JetpackClient(
    const std::string &ip, const std::string &port, bool debugMode)
    : _ip(ip), _port(port), _debugMode(debugMode), _running(true), _network(ip, port),
      _state(CLIENT_STATE::UNDEFIDED), _MapIsRetrieve(false)
{}

client::JetpackClient::~JetpackClient() {}

std::uint8_t client::JetpackClient::runClient()
{
    this->_running = true;
    this->_displayEngine.deactivateWindow();
    std::exception_ptr ThreadException = nullptr;

    std::thread networkThread(&JetpackClient::_runNetworkThread, this);
    std::thread displayThread(&JetpackClient::_runDisplayThread, this);

    networkThread.join();
    displayThread.join();

    return RET_SUCCESS;
}
