//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// ThreadNetwork.cpp
//

#include "JetpackClient.hpp"
#include <iostream>
#include <string>

void client::JetpackClient::runNetworkThread()
{
    while (this->_running) {
        this->_network.retrieveServerInformation();
        auto data = this->_network.getCommand();

        if (!data.empty()) {
            std::lock_guard<std::mutex> lock(this->data_mutex);
            this->_data.push(data);
        }
    }
}
