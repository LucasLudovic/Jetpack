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
#include <memory>
#include <vector>

namespace client {
    class Display {
       public:
        Display();
        ~Display();

        void renderFrame(
            const Player &player, const std::vector<std::string> &map);

       private:
        std::unique_ptr<sf::RenderWindow> _window = nullptr;
        std::unique_ptr<sf::Font> _font = nullptr;
        std::vector<client::Inputs> _events;

        sf::Sprite _player;
        sf::Sprite _coin;
        sf::Sprite _laser;
        void _loadAssets();
    };
}  // namespace client
