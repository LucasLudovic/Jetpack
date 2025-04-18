//
// EPITECH PROJECT, 2025
// Player
// File description:
// Player
//

#pragma once

#include <cstddef>
#include <vector>

namespace client {
    class Player {
       public:
        Player() = default;
        ~Player() = default;

        void setPosX(float value) { this->_posX = value; };

        void setPosY(float value) { this->_posY = value; };

        void setScore(size_t value) { this->_score = value; };

        void setPlayerAlive(bool value) { this->_playerAlive = value; }

        [[nodiscard]] float getPosX() const { return this->_posX; };

        [[nodiscard]] float getPosY() const { return this->_posY; };

        [[nodiscard]] size_t getScore() const { return this->_score; };

        [[nodiscard]] bool getPlayerAlive() const { return this->_playerAlive; };

       private:
        float _posX = 0;
        float _posY = 0;
        size_t _score = 0;
        bool _playerAlive = true;
        std::vector<size_t> _otherScore;
    };
}  // namespace client
