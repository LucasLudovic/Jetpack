//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Display.cpp
//

#include "Display.hpp"
#include "Inputs/Inputs.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <exception>
#include <map>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

client::Display::Display()
{
    this->_window =
        std::make_unique<sf::RenderWindow>(sf::VideoMode({900, 900}), "");
    if (!this->_window)
        throw DisplayError("Unable to render a window");

    this->_loadAssets();
}

client::Display::~Display()
{
    if (this->_window)
        this->_window->close();
}

void client::Display::_loadAssets()
{
    this->_font = std::make_unique<sf::Font>();
    this->_font->loadFromFile(
        "./assets/fonts/JetBrainsMonoNerdFont-Medium.ttf");
    if (this->_font == nullptr)
        throw DisplayError("Can't load the font");

    this->_loadCoinAssets();
    this->_loadPlayerAssets();
    this->_loadLaserAssets();
}

void client::Display::_loadCoinAssets()
{
    const int height = 171;
    const int width = 192;

    if (!this->_coinTexture.loadFromFile("assets/coins_sprite_sheet.png")) {
        throw DisplayError("Unable to load coinTexture");
    }
    for (int i = 0; i < this->_coinTexture.getSize().x / width; i += 1) {
        auto coinSprite = std::make_unique<sf::Sprite>();
        sf::IntRect rect(i * width, 0, width, height);

        if (!coinSprite) {
            throw DisplayError("For an unknown reason, we couldn't create a "
                               "unique_ptr for the coinSprite");
        }
        coinSprite->setTexture(this->_coinTexture);
        coinSprite->setTextureRect(rect);
        this->_coin.push_back(std::move(coinSprite));
    }
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

void client::Display::_loadLaserAssets()
{
    const int height = 171;
    const int width = 192;

    if (!this->_laserTexture.loadFromFile("assets/zapper_sprite_sheet.png")) {
        throw DisplayError("Unable to load laserTexture");
    }
    for (int i = 0; i < this->_laserTexture.getSize().x / width; i += 1) {
        auto laserSprite = std::make_unique<sf::Sprite>();
        sf::IntRect rect(i * width, 0, width, height);

        if (!laserSprite) {
            throw DisplayError("For an unknown reason, we couldn't create a "
                               "unique_ptr for the laserSprite");
        }
        laserSprite->setTexture(this->_laserTexture);
        laserSprite->setTextureRect(rect);
        this->_laser.push_back(std::move(laserSprite));
    }
}

void client::Display::_loadPlayerAssets()
{
    if (!this->_playerTexture.loadFromFile("assets/player_sprite_sheet.png")) {
        throw DisplayError("Unable to load playerTexture");
    }
    this->_loadPlayerRunAssets();
    this->_loadPlayerDieAssets();
    this->_loadPlayerFlightAssets();
}

void client::Display::_loadPlayerRunAssets()
{
    const int columns = 4;
    const int rows = 6;
    const int spriteWidth = this->_playerTexture.getSize().x / columns;
    const int spriteHeight = this->_playerTexture.getSize().y / rows;
    const int rowIndex = 0;

    for (size_t i = 0; i < columns; i += 1) {
        auto sprite = std::make_unique<sf::Sprite>();
        sprite->setTexture(_playerTexture);
        sprite->setTextureRect(sf::IntRect(i * spriteWidth,
            rowIndex * spriteHeight, spriteWidth, spriteHeight));
        this->_playerRun.push_back(std::move(sprite));
    }
}

void client::Display::_loadPlayerFlightAssets()
{
    const int columns = 4;
    const int rows = 6;
    const int spriteWidth = this->_playerTexture.getSize().x / columns;
    const int spriteHeight = this->_playerTexture.getSize().y / rows;
    const int rowIndex = 2;

    for (size_t i = 0; i < columns; i += 1) {
        auto sprite = std::make_unique<sf::Sprite>();
        sprite->setTexture(_playerTexture);
        sprite->setTextureRect(sf::IntRect(i * spriteWidth,
            rowIndex * spriteHeight, spriteWidth, spriteHeight));
        this->_playerFlight.push_back(std::move(sprite));
    }
}

void client::Display::_loadPlayerDieAssets()
{
    const int columns = 4;
    const int rows = 6;
    const int spriteWidth = this->_playerTexture.getSize().x / columns;
    const int spriteHeight = this->_playerTexture.getSize().y / rows;
    const int rowIndex = 4;

    for (size_t i = 0; i < columns; i += 1) {
        auto sprite = std::make_unique<sf::Sprite>();
        sprite->setTexture(_playerTexture);
        sprite->setTextureRect(sf::IntRect(i * spriteWidth,
            rowIndex * spriteHeight, spriteWidth, spriteHeight));
        this->_playerDie.push_back(std::move(sprite));
    }
}

void client::Display::renderFrame(
    const Player &player, const std::vector<std::string> &map)
{}
