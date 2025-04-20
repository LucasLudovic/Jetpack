//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Display.hpp
//

#pragma once

#include "Player/Player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <vector>

namespace client {

/**
 * @class Display
 * @brief Handles all rendering and event management using SFML.
 */
class Display {
   public:
    /**
     * @class DisplayError
     * @brief Exception class used to report errors during display operations.
     */
    class DisplayError : public std::exception {
       public:
        /**
         * @brief Constructs a DisplayError with the given message.
         * @param msg The error message.
         */
        DisplayError(const std::string &msg) { this->_msg = msg; }

        /**
         * @brief Returns the error message.
         * @return A C-style string containing the error message.
         */
        const char *what() const noexcept override
        {
            return this->_msg.c_str();
        }

       private:
        std::string _msg; ///< The error message
    };

    /**
     * @brief Constructs a Display object and initializes the window and resources.
     */
    Display();

    /**
     * @brief Destroys the Display object and releases resources.
     */
    ~Display();

    /**
     * @brief Renders one frame of the game, including players and map.
     * @param player First player.
     * @param player2 Second player.
     * @param map The current game map.
     */
    void renderFrame(
        const Player &player, const Player &player2, const std::vector<std::string> &map);

    /**
     * @brief Renders the end game screen with the results.
     * @param player First player.
     * @param player2 Second player.
     */
    void renderEndGame(const Player &player, const Player &player2);

    /**
     * @brief Handles user and window events.
     * @return True if an Event is detected, false otherwise.
     */
    bool handleEvent();

    /**
     * @brief Deactivates the rendering window (useful for multithreaded rendering).
     */
    void deactivateWindow();

    /**
     * @brief Activates the rendering window (useful for multithreaded rendering).
     */
    void activateWindow();

   private:
    const int _nbCols = 10; ///< Number of columns in the map grid.
    const int _nbRows = 10; ///< Number of rows in the map grid.

    float _startX = 0; ///< Viewport starting X coordinate.
    float _endX = 10;  ///< Viewport ending X coordinate.

    std::unique_ptr<sf::RenderWindow> _window = nullptr; ///< The SFML rendering window.
    std::unique_ptr<sf::Font> _font = nullptr; ///< The font used for displaying text.

    sf::Texture _coinTexture; ///< Texture for coins.
    sf::Texture _laserTexture; ///< Texture for lasers.
    sf::Texture _playerTexture; ///< Texture for the player.
    sf::Texture _backgroundTexture; ///< Texture for the background.

    sf::Sprite _backgroundSprite; ///< Sprite representing the background.
    std::vector<std::unique_ptr<sf::Sprite>> _coin; ///< Sprites for coin objects.
    std::vector<std::unique_ptr<sf::Sprite>> _laser; ///< Sprites for laser objects.

    std::vector<std::unique_ptr<sf::Sprite>> _playerRun; ///< Sprites for player running animation.
    std::vector<std::unique_ptr<sf::Sprite>> _playerDie; ///< Sprites for player death animation.
    std::vector<std::unique_ptr<sf::Sprite>> _playerFlight; ///< Sprites for player flying animation.

    /**
     * @brief Loads the font used in the UI.
     */
    void _loadFont();

    /**
     * @brief Loads all assets needed by the display.
     */
    void _loadAssets();

    /**
     * @brief Loads the background image asset.
     */
    void _loadBackgroundAsset();

    /**
     * @brief Loads all coin sprite assets.
     */
    void _loadCoinAssets();

    /**
     * @brief Loads the general player sprite asset.
     */
    void _loadPlayerAssets();

    /**
     * @brief Loads the player running animation frames.
     */
    void _loadPlayerRunAssets();

    /**
     * @brief Loads the player death animation frames.
     */
    void _loadPlayerDieAssets();

    /**
     * @brief Loads the player flying animation frames.
     */
    void _loadPlayerFlightAssets();

    /**
     * @brief Loads all laser sprite assets.
     */
    void _loadLaserAssets();

    /**
     * @brief Draws the background to the screen.
     */
    void _drawBackground();

    /**
     * @brief Draws the player's sprite on the map.
     * @param player The player to draw.
     * @param map The current game map.
     */
    void _drawPlayer(
        const Player &player, const std::vector<std::string> &map);

    /**
     * @brief Draws map elements such as coins and lasers.
     * @param player The player (may be used for conditional rendering).
     * @param map The current game map.
     */
    void _drawProps(
        const Player &player, const std::vector<std::string> &map);

    /**
     * @brief Draws the in-game HUD (scores, etc.).
     * @param player First player.
     * @param player2 Second player.
     */
    void _drawAth(const Player &player, const Player &player2);

    /**
     * @brief Draws the end-of-game screen with final scores.
     * @param player First player.
     * @param player2 Second player.
     */
    void _drawEnd(const Player &player, const Player &player2);
};

}  // namespace client

