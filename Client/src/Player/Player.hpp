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

/**
 * @enum WIN_STATE
 * @brief Represents the outcome of a player's game.
 */
enum class WIN_STATE : std::uint8_t {
    WIN,       ///< The player won the game.
    LOSE,      ///< The player lost the game.
    DRAW,      ///< The game ended in a draw.
    UNDEFINED  ///< The result has not been determined yet.
};

/**
 * @class Player
 * @brief Represents a player in the game, with position, score, and state.
 */
class Player {
   public:
    /**
     * @brief Default constructor for Player.
     */
    Player() = default;

    /**
     * @brief Default destructor for Player.
     */
    ~Player() = default;

    /**
     * @brief Sets the player's X position.
     * @param value The X coordinate.
     */
    void setPosX(float value) { this->_posX = value; };

    /**
     * @brief Sets the player's Y position.
     * @param value The Y coordinate.
     */
    void setPosY(float value) { this->_posY = value; };

    /**
     * @brief Sets the player's score.
     * @param value The score value.
     */
    void setScore(size_t value) { this->_score = value; };

    /**
     * @brief Sets the player's win state.
     * @param value The win state (WIN, LOSE, DRAW, UNDEFINED).
     */
    void setPlayerWin(WIN_STATE value) { this->_hasWin = value; }

    /**
     * @brief Sets the player's number (ID or index).
     * @param value The player number.
     */
    void setPlayerNumber(ssize_t value) { this->_playerNumber = value; }

    /**
     * @brief Sets the player's transparency state.
     * @param value True if the player should be transparent.
     */
    void setPlayerTransparency(bool value) { this->_playerTransparency = value; }

    /**
     * @brief Gets the player's X position.
     * @return The X coordinate.
     */
    [[nodiscard]] float getPosX() const { return this->_posX; };

    /**
     * @brief Gets the player's Y position.
     * @return The Y coordinate.
     */
    [[nodiscard]] float getPosY() const { return this->_posY; };

    /**
     * @brief Gets the player's current score.
     * @return The score.
     */
    [[nodiscard]] size_t getScore() const { return this->_score; };

    /**
     * @brief Gets the player's win state.
     * @return The win state (WIN, LOSE, DRAW, UNDEFINED).
     */
    [[nodiscard]] WIN_STATE getPlayerWin() const { return this->_hasWin; };

    /**
     * @brief Gets the player's number (ID or index).
     * @return The player number.
     */
    [[nodiscard]] ssize_t getPlayerNumber() const { return this->_playerNumber; };

    /**
     * @brief Checks whether the player is transparent.
     * @return True if the player is transparent.
     */
    [[nodiscard]] bool getPlayerTransparency() const { return this->_playerTransparency; };

   private:
    float _posX = 0; ///< The X position of the player.
    float _posY = 0; ///< The Y position of the player.
    size_t _score = 0; ///< The current score of the player.
    WIN_STATE _hasWin = WIN_STATE::UNDEFINED; ///< The result of the game for the player.
    ssize_t _playerNumber = 0; ///< Player's identifier or number.
    bool _playerTransparency = false; ///< Whether the player is transparent (e.g., ghosted).
};

}  // namespace client

