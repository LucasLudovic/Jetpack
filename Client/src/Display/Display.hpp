//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Display.hpp
//

#pragma once

#include "Inputs/Inputs.hpp"
#include "Player/Player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <vector>

namespace client {
    class Display {
       public:
        class DisplayError : public std::exception {
           public:
            DisplayError(const std::string &msg) { this->_msg = msg; }

            const char *what() const noexcept override
            {
                return this->_msg.c_str();
            }

           private:
            std::string _msg;
        };

        Display();
        ~Display();

        void renderFrame(
            const Player &player, const std::vector<std::string> &map);

        bool handleEvent();

        void deactivateWindow();
        void activateWindow();

       private:
        const int _nbCols = 10;
        const int _nbRows = 10;

        float _startX = 0;
        float _endX = 10;

        std::unique_ptr<sf::RenderWindow> _window = nullptr;
        std::unique_ptr<sf::Font> _font = nullptr;
        std::vector<client::Inputs> _events;

        sf::Texture _coinTexture;
        sf::Texture _laserTexture;
        sf::Texture _playerTexture;
        sf::Texture _backgroundTexture;

        sf::Sprite _backgroundSprite;
        std::vector<std::unique_ptr<sf::Sprite>> _coin;
        std::vector<std::unique_ptr<sf::Sprite>> _laser;

        std::vector<std::unique_ptr<sf::Sprite>> _playerRun;
        std::vector<std::unique_ptr<sf::Sprite>> _playerDie;
        std::vector<std::unique_ptr<sf::Sprite>> _playerFlight;

        void _loadFont();
        void _loadAssets();
        void _loadBackgroundAsset();
        void _loadCoinAssets();
        void _loadPlayerAssets();
        void _loadPlayerRunAssets();
        void _loadPlayerDieAssets();
        void _loadPlayerFlightAssets();
        void _loadLaserAssets();

        void _drawBackground();
        void _drawPlayer(const Player &player, const std::vector<std::string> &map);
        void _drawProps(const std::vector<std::string> &map);
    };
}  // namespace client
