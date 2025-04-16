//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// ThreadDisplay.cpp
//

#include "JetpackClient.hpp"
#include <cstddef>
#include <functional>
#include <iostream>
#include <map>
#include <thread>

void client::JetpackClient::handleWaitingPlayers()
{
    std::cout << "Waiting Player\n";
    this->_state = CLIENT_STATE::WAITING;
}

void client::JetpackClient::startMap()
{
    std::cout << "MAP START\n";
    this->_retrieveMap = true;
}

void client::JetpackClient::retrieveMap(const std::string &map)
{
    size_t starting = 0;
    size_t value = 0;

    if (map.empty())
        throw ClientError("Map was not send");

    value = map.find('\n');

    while ((value = map.find('\n', starting)) != std::string::npos) {
        this->_map.push_back(map.substr(starting, value - starting));
        starting = value + 1;
    }
    if (starting < map.size()) {
        this->_map.push_back(map.substr(starting));
    }
}

void client::JetpackClient::endMap()
{
    std::cout << "MAP END\n";
    this->_retrieveMap = false;
}

void client::JetpackClient::handleDisplay()
{
    std::map<std::string, std::function<void()>> instructions{
        {"WAITING_PLAYERS",
            [this] {
                handleWaitingPlayers();
            }},
        {"START_MAP",
            [this] {
                startMap();
            }},
        {"END_MAP",
            [this] {
                endMap();
            }},
    };

    std::lock_guard<std::mutex> lock(this->data_mutex);
    if (this->_data.empty()) {
        return;
    }

    std::string currentData = this->_data.front();
    for (const auto &it : instructions) {
        if (currentData == it.first) {
            it.second();
            this->_data.pop();
            break;
        }
        if (this->_retrieveMap) {
            this->retrieveMap(currentData);
            this->_data.pop();
            break;
        }
    }
}

void client::JetpackClient::runDisplayThread()
{
    while (this->_running) {
        this->handleDisplay();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
