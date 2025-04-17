//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Display.cpp
//

#include "Display.hpp"
#include "Inputs/Inputs.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <map>
#include <exception>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

client::Display::Display()
{
    this->_window =
        std::make_unique<sf::RenderWindow>(sf::VideoMode({900, 900}), "");

    this->_font = std::make_unique<sf::Font>();
    this->_font->loadFromFile(
        "./assets/fonts/JetBrainsMonoNerdFont-Medium.ttf");
    if (this->_font == nullptr || this->_window == nullptr)
        throw std::exception();
}

client::Display::~Display()
{
    if (this->_window)
        this->_window->close();
}

void client::Display::_loadAssets()
{
    sf::Texture coin;
    coin.loadFromFile("assets/coin.jpg");

    this->_coin.setTexture(coin, false);
}

void client::Display::renderFrame(const Player &player, const std::vector<std::string> &map)
{
}

bool client::Display::handleEvent()
{
    sf::Event sfmlEvent;
    bool Event;

    while (this->_window->pollEvent(sfmlEvent)) {
        switch (sfmlEvent.type) {
            case sf::Event::KeyPressed: {
                Event = true;
                break;
            }
            default:
                break;
        }
    }
    return Event;
}
