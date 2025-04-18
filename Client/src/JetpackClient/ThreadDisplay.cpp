//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// ThreadDisplay.cpp
//

#include "JetpackClient.hpp"
#include "client.hpp"
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
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

void client::JetpackClient::startGame()
{
    std::cout << "START GAME\n";
    this->_state = CLIENT_STATE::PLAYING;
}

void client::JetpackClient::_updatePlayerPosition(const std::string &pos)
{
    if (pos.find("position:") != std::string::npos) {
        size_t value = pos.find(":x=");
        size_t value2 = pos.find(":y=");
        size_t value3 = pos.find(":s=");
        std::string posX = pos.substr(value + 3, value2 - value - 3);
        std::string posY = pos.substr(value2 + 3, value3 - value2 - 3);
        std::string score = pos.substr(value3 + 3);
        this->_player.setPosX(std::atof(posX.c_str()));
        this->_player.setPosY(std::atof(posY.c_str()));
        this->_player.setScore(std::atoi(score.c_str()));
    }
}

void client::JetpackClient::_retrieveCoin()
{
    const float playerX = this->_player.getPosX();
    const float playerY = this->_player.getPosY();

    const float hitboxWidth = 0.7;
    const float hitboxHeight = 0.7;

    const float left = playerX - (hitboxWidth / 2.0);
    const float right = playerX + (hitboxWidth / 2.0);
    const float bottom = playerY - (hitboxHeight / 2.0);
    const float top = playerY + (hitboxHeight / 2.0);

    const int startX = static_cast<int>(left);
    const int endX = static_cast<int>(right);
    const int startY = static_cast<int>(bottom);
    const int endY = static_cast<int>(top);

    for (int y = startY; y <= endY; ++y) {
        for (int x = startX; x <= endX; ++x) {
            int mapY = 9 - y;
            if (mapY >= 0 && mapY < static_cast<int>(_map.size()) && x >= 0 &&
                x < static_cast<int>(_map[0].size())) {

                if (_map[mapY][x] == 'c') {
                    _map[mapY][x] = '_';
                }
            }
        }
    }
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
        {"GAME_START:0",
            [this] {
                startGame();
            }},
        {"GAME_START:1",
            [this] {
                startGame();
            }},
    };
    {
        std::lock_guard<std::mutex> lock(this->data_mutex);
        if (this->_data.empty()) {
            return;
        }
    }
    std::string currentData = this->_data.front();
    if (this->_state == CLIENT_STATE::PLAYING) {
        this->_updatePlayerPosition(currentData);
        if (currentData == "GAME_END") {
            std::cout << "Game End" << std::endl;
            exit(0);
        }
        if (currentData == "DIED")
            this->_player.setPlayerAlive(false);
        this->_retrieveCoin();
        this->_displayEngine.renderFrame(this->_player, this->_map);
        this->_data.pop();
        if (this->_displayEngine.handleEvent())
            this->_msg.push("PRESSED");
        return;
    }
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
    try {
        this->_displayEngine.activateWindow();
        while (this->_running) {
            this->handleDisplay();
        }
    } catch (...) {
        exit(RET_FAILURE);
    }
}
