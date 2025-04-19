//
// EPITECH PROJECT, 2025
// Player
// File description:
// Player
//

#pragma once

#include <cstddef>
#include <sys/types.h>
#include <vector>

namespace client {
    class Player {
       public:
        Player() = default;
        ~Player() = default;

        void setPosX(float value) { this->_posX = value; };

        void setPosY(float value) { this->_posY = value; };

        void setScore(size_t value) { this->_score = value; };

        void setPlayerWin(bool value) { this->_hasWin = value; }

        void setPlayerNumber(ssize_t value) { this->_playerNumber = value; }

        void setPlayerTransparency(bool value) { this->_playerTransparency = value; }

        [[nodiscard]] float getPosX() const { return this->_posX; };

        [[nodiscard]] float getPosY() const { return this->_posY; };

        [[nodiscard]] size_t getScore() const { return this->_score; };

        [[nodiscard]] bool getPlayerWin() const { return this->_hasWin; };

        [[nodiscard]] ssize_t getPlayerNumber() const { return this->_playerNumber; };

        [[nodiscard]] bool getPlayerTransparency() const { return this->_playerTransparency; };

       private:
        float _posX = 0;
        float _posY = 0;
        size_t _score = 0;
        bool _hasWin = false;
        ssize_t _playerNumber = 0;
        bool _playerTransparency = false;
    };
}  // namespace client
