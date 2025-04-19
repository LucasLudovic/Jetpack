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

        void setScoreOtherPlayer(size_t value) { this->_scoreOtherPlayer = value; };

        void setPlayerWin(bool value) { this->_hasWin = value; }

        void setPlayerNumber(ssize_t value) { this->_playerNumber = value; }

        [[nodiscard]] float getPosX() const { return this->_posX; };

        [[nodiscard]] float getPosY() const { return this->_posY; };

        [[nodiscard]] size_t getScore() const { return this->_score; };

        [[nodiscard]] bool getPlayerWin() const { return this->_hasWin; };

        [[nodiscard]] ssize_t getPlayerNumber() const { return this->_playerNumber; };

        [[nodiscard]] size_t getScoreOtherPlayer() const { return this->_scoreOtherPlayer; };

       private:
        float _posX = 0;
        float _posY = 0;
        size_t _score = 0;
        size_t _scoreOtherPlayer = 0;
        bool _hasWin = false;
        ssize_t _playerNumber = 0;
        std::vector<size_t> _otherScore;
    };
}  // namespace client
