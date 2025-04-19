//
// EPITECH PROJECT, 2025
// Player
// File description:
// Player
//

#pragma once

#include <cstddef>
#include <cstdint>
#include <sys/types.h>

namespace client {
    enum class WIN_STATE : std::uint8_t { WIN, LOSE, DRAW, UNDEFINED };

    class Player {
       public:
        Player() = default;
        ~Player() = default;

        void setPosX(float value) { this->_posX = value; };

        void setPosY(float value) { this->_posY = value; };

        void setScore(size_t value) { this->_score = value; };

        void setPlayerWin(WIN_STATE value) { this->_hasWin = value; }

        void setPlayerNumber(ssize_t value) { this->_playerNumber = value; }

        void setPlayerTransparency(bool value) { this->_playerTransparency = value; }

        [[nodiscard]] float getPosX() const { return this->_posX; };

        [[nodiscard]] float getPosY() const { return this->_posY; };

        [[nodiscard]] size_t getScore() const { return this->_score; };

        [[nodiscard]] WIN_STATE getPlayerWin() const { return this->_hasWin; };

        [[nodiscard]] ssize_t getPlayerNumber() const { return this->_playerNumber; };

        [[nodiscard]] bool getPlayerTransparency() const { return this->_playerTransparency; };

       private:
        float _posX = 0;
        float _posY = 0;
        size_t _score = 0;
        WIN_STATE _hasWin = WIN_STATE::UNDEFINED;
        ssize_t _playerNumber = 0;
        bool _playerTransparency = false;
    };
}  // namespace client
