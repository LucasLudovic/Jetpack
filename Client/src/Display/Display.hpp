//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Display.hpp
//

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "../Inputs/Inputs.hpp"

namespace client {
    class Display {
       public:
        Display();
        ~Display();

        void drawEntity(const std::string &texturePath, float posx, float posy, float scalex, float scaley);

        void drawText(const std::string &str, float posx, float posy);

        std::vector<Inputs> &getEvents();

        void render();

        void clear();

       private:
        std::unique_ptr<sf::RenderWindow> _window = nullptr;
        std::unique_ptr<sf::Font> _font = nullptr;
        std::vector<client::Inputs> _events;
    };
}  // namespace client
