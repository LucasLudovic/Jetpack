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
#include <map>
#include <mutex>
#include <string>
#include <thread>

client::JetpackClient::JetpackClient(
    const std::string &ip, const std::string &port)
    : _ip(ip), _port(port), _running(true), _network(ip, port)
{}

client::JetpackClient::~JetpackClient() {}

void client::JetpackClient::runNetworkThread()
{
    while (this->_running) {
        std::cout << "SERVER\n";
        auto data = this->_network.retrieveServerInformation();
        
        if (!data.empty()) {
            std::lock_guard<std::mutex> lock(this->data_mutex);
            this->_data.push(data);
        }
        std::cout << "SERVER2\n";
    }
}

void client::JetpackClient::runDisplayThread()
{
    while (this->_running) {
        std::cout << "Client\n";
        this->handleDisplay();
        std::cout << "Client2\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}


void client::JetpackClient::handleWaitingPlayers()
{
    std::cout << "Waiting Player\n";
}

void client::JetpackClient::handleDisplay()
{
    using pfunc = void (client::JetpackClient::*)();
    std::map<std::string, pfunc> instructions {
        {"WAITING_PLAYERS", &client::JetpackClient::handleWaitingPlayers},
        {"220 Connection established.\r\n", &client::JetpackClient::handleWaitingPlayers}
    };
    
    std::lock_guard<std::mutex> lock(this->data_mutex);
    if (this->_data.empty()) {
        return;
    }
    
    std::string currentData = this->_data.front();
    for (const auto &it : instructions) {
        if (currentData == it.first) {
            (this->*it.second)();
            this->_data.pop();
            break;
        }
    }
}

std::uint8_t client::JetpackClient::runClient()
{
    this->_running = true;

    std::thread networkThread(&JetpackClient::runNetworkThread, this);
    
    std::thread displayThread(&JetpackClient::runDisplayThread, this);
    
    networkThread.join();
    displayThread.join();
    
    return RET_SUCCESS;
}
