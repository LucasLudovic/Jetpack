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
#include <mutex>
#include <string>
#include <thread>

client::JetpackClient::JetpackClient(
    const std::string &ip, const std::string &port)
    : _ip(ip), _port(port), _running(true)
{}

client::JetpackClient::~JetpackClient() {}

std::uint8_t client::JetpackClient::runClient()
{
    client::Network network(this->_ip, this->_port);
    std::mutex data_mutex;

    std::thread t1([&]() {
        while (this->_running) {
            for (const auto &it : this->_msg)
                network.sendInputToServer(it);
            {
                std::lock_guard<std::mutex> lock(data_mutex);
                this->_data.push_back(network.retrieveServerInformation());
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    });
    std::thread t2([&]() {
        while (this->_running) {
            {
                std::lock_guard<std::mutex> lock(data_mutex);
                for (const auto &info : this->_data) {
                    std::cout << info << std::endl;
                }
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    t1.join();
    t2.join();
    return RET_SUCCESS;
}
