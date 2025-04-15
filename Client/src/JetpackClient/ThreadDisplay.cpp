//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// ThreadDisplay.cpp
//

#include "JetpackClient.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <thread>

void client::JetpackClient::handleWaitingPlayers()
{
    std::cout << "Waiting Player\n";
    this->_state = CLIENT_STATE::WAITING;
}

void client::JetpackClient::handleDisplay()
{
    std::map<std::string, std::function<void()>> instructions{
        {"WAITING_PLAYERS\r\n",
            [this] {
                handleWaitingPlayers();
            }},
        {"220 Connection established.\r\n", [this] {
             handleWaitingPlayers();
         }}};

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
    }
}

void client::JetpackClient::runDisplayThread()
{
    while (this->_running) {
        this->handleDisplay();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
