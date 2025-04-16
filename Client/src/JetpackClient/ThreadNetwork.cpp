//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// ThreadNetwork.cpp
//

#include "JetpackClient.hpp"
#include <iostream>
#include <string>

void client::JetpackClient::retrieveMap()
{
    // auto map = this->_network.retrieveServerInformation();
    // int starting = 0;
    // int value = 0;
    //
    // if (map.empty())
    //     throw ClientError("Map was not send");
    //
    // value = map.find('\n');
    // while (value != std::string::npos) {
    //     this->_map.push_back(map.substr(starting, value));
    //     starting = value + 1;
    // }
    // for (const auto &it : this->_map) {
    //     std::cout << "map = " << it << '\n';
    // }
}

void client::JetpackClient::setupGame()
{
    // auto cmd = this->_network.retrieveServerInformation();
    // std::cout << "cmd = " << cmd << '\n';
    // if (cmd == "WAITING_PLAYERS\r\n") {
    //     this->_state = CLIENT_STATE::WAITING;
    // } else {
    //     throw ClientError(
    //         "Server must send Waiting players as first message");
    // }
    // std::string isMap;
    // while (isMap.empty())
    // std::cout << "Waiting Send Map = " << isMap << '\n';
    // if (isMap == "SEND_MAP\r\n") {
    //     this->retrieveMap();
    // }
}

void client::JetpackClient::runNetworkThread()
{
    while (this->_running) {
        this->_network.retrieveServerInformation();
        auto data = this->_network.getCommand();

        if (!data.empty())
            std::cout << "data = " << data << '\n';
        if (!data.empty()) {
            std::lock_guard<std::mutex> lock(this->data_mutex);
            this->_data.push(data);
        }
    }
}
