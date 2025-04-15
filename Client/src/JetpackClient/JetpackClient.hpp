//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// JetpackClient.hpp
//

#pragma once

#include "Network/Network.hpp"
#include <cstdint>
#include <mutex>
#include <queue>
#include <string>

namespace client {
    class JetpackClient {
       public:
        JetpackClient(const std::string &ip, const std::string &port);
        ~JetpackClient();

        std::uint8_t runClient();

       private:
        std::string _ip;
        std::string _port;
        bool _running;
        std::queue<std::string> _data;
        std::queue<std::string> _msg;
        std::mutex data_mutex;
        client::Network _network;

        void retrieveDataServer();
        void handleDisplay();

        void handleWaitingPlayers();
        void runNetworkThread();
        void runDisplayThread();
    };
}  // namespace client
