//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// JetpackClient.hpp
//

#pragma once

#include "Display/Display.hpp"
#include "Network/Network.hpp"
#include "Player/Player.hpp"
#include <cstdint>
#include <mutex>
#include <queue>
#include <string>
#include <vector>

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

        JetpackClient(const std::string &ip, const std::string &port, bool debugMode);
        ~JetpackClient();

        std::uint8_t runClient();

       private:
        std::string _ip;
        std::string _port;
        bool _debugMode;
        bool _running;
        CLIENT_STATE _state;
        std::queue<std::string> _data;
        std::queue<std::string> _msg;
        std::mutex data_mutex;
        client::Network _network;
        client::Display _displayEngine;
        Player _player;
        Player _player2;
        bool _MapIsRetrieve;
        std::vector<std::string> _map;

        void _runNetworkThread();
        void _runDisplayThread();

        void _retrieveDataServer();
        void _handleDisplay();
        void _gameRunning(const std::string &currentData);
        void _sendMessage();

        void _handleWaitingPlayers();
        void _startMap();
        void _retrieveMap(const std::string &map);
        void _endMap();
        void _startGamePlayerOne();
        void _startGamePlayerTwo();
        void _updatePlayerPosition(const std::string &pos);
        void _retrieveCoin();
    };
}  // namespace client
