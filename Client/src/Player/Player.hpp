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

        void setPosX(size_t value) { this->_posX = value; };

        void setPosY(size_t value) { this->_posY = value; };

        void setScore(size_t value) { this->_score = value; };

        [[nodiscard]] size_t getPosX() const { return this->_posX; };

        [[nodiscard]] size_t getPosY() const { return this->_posY; };

        [[nodiscard]] size_t getScore() const { return this->_score; };

       private:
        size_t _posX = 0;
        size_t _posY = 0;
        size_t _score = 0;
        std::vector<size_t> _otherScore;
    };
}  // namespace client
