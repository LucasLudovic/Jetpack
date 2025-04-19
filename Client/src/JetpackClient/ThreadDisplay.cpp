//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// ThreadDisplay.cpp
//

#include "JetpackClient.hpp"
#include "Player/Player.hpp"
#include "client.hpp"
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <map>
#include <string>

void client::JetpackClient::_handleWaitingPlayers()
{
    this->_state = CLIENT_STATE::WAITING;
}

void client::JetpackClient::_startMap()
{
    this->_MapIsRetrieve = true;
}

void client::JetpackClient::_retrieveMap(const std::string &map)
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

void client::JetpackClient::_endMap()
{
    this->_MapIsRetrieve = false;
}

void client::JetpackClient::_startGamePlayerOne()
{
    this->_player.setPlayerNumber(1);
    this->_player.setPlayerTransparency(false);
    this->_player2.setPlayerNumber(2);
    this->_player2.setPlayerTransparency(true);
    this->_state = CLIENT_STATE::PLAYING;
}

void client::JetpackClient::_startGamePlayerTwo()
{
    this->_player.setPlayerNumber(2);
    this->_player.setPlayerTransparency(false);
    this->_player2.setPlayerNumber(1);
    this->_player2.setPlayerTransparency(true);
    this->_state = CLIENT_STATE::PLAYING;

}

void client::JetpackClient::_updatePlayerPosition(const std::string &pos)
{
    if (pos.find("position:") != std::string::npos) {
        size_t value = pos.find(":x=");
        size_t value2 = pos.find(":y=");
        size_t value3 = pos.find(":y2=");
        size_t value4 = pos.find(":s1=");
        size_t value5 = pos.find(",s2=");
        std::string posX = pos.substr(value + 3, value2 - value - 3);
        std::string posY = pos.substr(value2 + 3, value3 - value2 - 3);
        std::string posY2 = pos.substr(value3 + 4, value4 - value3 - 4);
        std::string scorePlayerOne = pos.substr(value4 + 4, value5 - value4 - 4);
        std::string scorePlayerTwo = pos.substr(value5 + 4);
        this->_player.setPosX(std::atof(posX.c_str()));
        this->_player2.setPosX(std::atof(posX.c_str()));
        this->_player.setPosY(std::atof(posY.c_str()));
        this->_player2.setPosY(std::atof(posY2.c_str()));
        if (this->_player.getPlayerNumber() == 1) {
            this->_player.setScore(std::atoi(scorePlayerOne.c_str()));
            this->_player2.setScore(std::atoi(scorePlayerTwo.c_str()));
        } else {
            this->_player.setScore(std::atoi(scorePlayerTwo.c_str()));
            this->_player2.setScore(std::atoi(scorePlayerOne.c_str()));
        }
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

void client::JetpackClient::_gameRunning(const std::string &currentData)
{
    if (this->_state == CLIENT_STATE::PLAYING) {
        this->_updatePlayerPosition(currentData);
        if (currentData.find("WIN") != std::string::npos) {
            this->_player.setPlayerWin(WIN_STATE::WIN);
            this->_displayEngine.renderEndGame(this->_player, this->_player2);
            this->_displayEngine.handleEvent();
            return;
        }
        if (currentData.find("LOSE") != std::string::npos) {
            this->_player.setPlayerWin(WIN_STATE::LOSE);
            this->_displayEngine.renderEndGame(this->_player, this->_player2);
            this->_displayEngine.handleEvent();
            return;
        }
        if (currentData.find("DRAW") != std::string::npos) {
            this->_player.setPlayerWin(WIN_STATE::DRAW);
            this->_displayEngine.renderEndGame(this->_player, this->_player2);
            this->_displayEngine.handleEvent();
            return;
        }
        this->_retrieveCoin();
        this->_displayEngine.renderFrame(this->_player, this->_player2 ,this->_map);
        this->_data.pop();
        if (this->_displayEngine.handleEvent())
            this->_msg.push("PRESSED");
        return;
    }

}

void client::JetpackClient::_handleDisplay()
{
    std::map<std::string, std::function<void()>> instructions{
        {"WAITING_PLAYERS",
            [this] {
                _handleWaitingPlayers();
            }},
        {"START_MAP",
            [this] {
                _startMap();
            }},
        {"END_MAP",
            [this] {
                _endMap();
            }},
        {"GAME_START:0",
            [this] {
                _startGamePlayerOne();
            }},
        {"GAME_START:1",
            [this] {
                _startGamePlayerTwo();
            }},
    };
    {
        std::lock_guard<std::mutex> lock(this->data_mutex);
        if (this->_data.empty()) {
            return;
        }
    }
    std::string currentData = this->_data.front();
    this->_gameRunning(currentData);
    for (const auto &it : instructions) {
        if (currentData == it.first) {
            it.second();
            this->_data.pop();
            break;
        }
        if (this->_MapIsRetrieve) {
            this->_retrieveMap(currentData);
            this->_data.pop();
            break;
        }
    }
}

void client::JetpackClient::_runDisplayThread()
{
    try {
        this->_displayEngine.activateWindow();
        while (this->_running) {
            this->_handleDisplay();
        }
    } catch (...) {
        exit(RET_FAILURE);
    }
}
