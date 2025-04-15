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
    enum class CLIENT_STATE : std::uint8_t { UNDEFIDED, PLAYING, WAITING };

    class JetpackClient {
       public:
        class ClientError : public std::exception {
           public:
            ClientError(const std::string &msg) { this->_msg = msg; }

            const char *what() const noexcept override
            {
                return this->_msg.c_str();
            }

           private:
            std::string _msg;
        };
        JetpackClient(const std::string &ip, const std::string &port);
        ~JetpackClient();

        std::uint8_t runClient();

       private:
        std::string _ip;
        std::string _port;
        bool _running;
        CLIENT_STATE _state;
        std::queue<std::string> _data;
        std::queue<std::string> _msg;
        std::mutex data_mutex;
        client::Network _network;

        void setupGame();

        void runNetworkThread();
        void runDisplayThread();

        void retrieveDataServer();
        void handleDisplay();

        void handleWaitingPlayers();
    };
}  // namespace client
