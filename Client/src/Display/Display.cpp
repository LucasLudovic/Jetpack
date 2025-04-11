//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Display.cpp
//

#include "Display.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <exception>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>

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

void client::Display::drawEntity(const std::string &texturePath, float posx, float posy, float scalex, float scaley)
{
    sf::Texture texture;
    sf::Sprite sprite;

    if (texturePath.empty())
        throw std::exception();

    if (!texture.loadFromFile(texturePath))
        throw std::exception();

    sprite.setTexture(texture);
    sprite.setPosition(posx, posy);
    sprite.setScale(scalex, scaley);

    this->_window->draw(sprite);
}

void client::Display::drawText(
    const std::string &str, float posx, float posy)
{
    sf::Text text;

    if (!this->_font)
        throw std::exception();
    text.setFont(*this->_font);
    text.setString(str);
    text.setFillColor(sf::Color::White);
    text.setPosition(posx, posy);

    this->_window->draw(text);
}

void client::Display::render()
{
    this->_window->display();
}

void client::Display::clear()
{
    this->_window->clear();
}
