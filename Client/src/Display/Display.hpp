//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Display.hpp
//

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

namespace client {
    class Display {
       public:
        Display();
        ~Display();

        void drawEntity(const std::string &texturePath, float posx, float posy, float scalex, float scaley);

        void drawText(const std::string &str, float posx, float posy);

        void render();

        void clear();

       private:
        std::unique_ptr<sf::RenderWindow> _window = nullptr;
        std::unique_ptr<sf::Font> _font = nullptr;
    };
}  // namespace client
