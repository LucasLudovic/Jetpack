//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// ThreadNetwork.cpp
//

#include "JetpackClient.hpp"
#include <iostream>

void client::JetpackClient::runNetworkThread()
{
    while (this->_running) {
        auto data = this->_network.retrieveServerInformation();

        if (!data.empty()) {
            std::lock_guard<std::mutex> lock(this->data_mutex);
            std::cout << data;
            this->_data.push(data);
        }
    }
}
