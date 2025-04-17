//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// ThreadNetwork.cpp
//

#include "JetpackClient.hpp"
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

void client::JetpackClient::runNetworkThread()
{
    while (this->_running) {
        auto frameStart = std::chrono::steady_clock::now();
        this->_network.retrieveServerInformation();
        auto data = this->_network.getCommand();

        if (!data.empty()) {
            std::lock_guard<std::mutex> lock(this->data_mutex);
            this->_data.push(data);
        }
        if (this->_state == CLIENT_STATE::PLAYING) {
            if (!this->_msg.empty()) {
                std::cout << "Pressed\n";
                std::lock_guard<std::mutex> lock(this->data_mutex);
                this->_network.sendInputToServer(this->_msg.front());
                this->_msg.pop();
            } else {
                this->_network.sendInputToServer("GETPOS");
            }
        }
        auto frameEnd = std::chrono::steady_clock::now();
        auto frameDuration =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                frameEnd - frameStart);
        const std::chrono::milliseconds targetFrameDuration(100);
        if (frameDuration < targetFrameDuration) {
            std::this_thread::sleep_for(targetFrameDuration - frameDuration);
        }
    }
}
