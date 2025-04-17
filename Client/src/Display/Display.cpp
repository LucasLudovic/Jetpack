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
#include <iostream>
#include <map>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

client::Display::Display()
{
    std::cout << "Init display" << std::endl;
    this->_window =
        std::make_unique<sf::RenderWindow>(sf::VideoMode({900, 900}), "");
    if (!this->_window)
        throw DisplayError("Unable to render a window");

    this->_window->setActive(true);
    this->_loadAssets();
}

client::Display::~Display()
{
    std::cout << "Destroy display" << std::endl;
    if (this->_window)
        this->_window->close();
}

void client::Display::activateWindow()
{
    this->_window->setActive(true);
}

void client::Display::deactivateWindow()
{
    this->_window->setActive(false);
}

void client::Display::_loadAssets()
{
    std::cout << "Loading assets" << std::endl;
    this->_font = std::make_unique<sf::Font>();
    this->_font->loadFromFile(
        "./assets/fonts/JetBrainsMonoNerdFont-Medium.ttf");
    if (this->_font == nullptr)
        throw DisplayError("Can't load the font");

    this->_loadCoinAssets();
    this->_loadPlayerAssets();
    this->_loadLaserAssets();
    std::cout << "Done loading assets" << std::endl;
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
{
    const float spriteWidth = static_cast<float>(this->_window->getSize().x) /
                              static_cast<float>(map[0].size());
    const float spriteHeight = static_cast<float>(this->_window->getSize().y) /
                               static_cast<float>(map.size());

    static size_t frameCounter = 0;
    const size_t coinFrame = frameCounter % _coin.size();
    const size_t laserFrame = frameCounter % _laser.size();

    this->_window->clear();
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            char tile = map[y][x];
            sf::Vector2f position(x * spriteWidth, y * spriteHeight);

            if (tile == 'c') {
                auto &sprite = *this->_coin[coinFrame];
                sprite.setPosition(position);
                sprite.setScale(spriteWidth / sprite.getLocalBounds().width,
                    spriteHeight / sprite.getLocalBounds().height);
                this->_window->draw(sprite);
            }
            if (tile == 'e') {
                auto &sprite = *this->_laser[laserFrame];
                sprite.setPosition(position);
                sprite.setScale(spriteWidth / sprite.getLocalBounds().width,
                    spriteHeight / sprite.getLocalBounds().height);
                this->_window->draw(sprite);
            }
        }
    }
    frameCounter += 1;
    this->_drawPlayer(player, map);
    this->_window->display();
}

void client::Display::_drawPlayer(
    const Player &player, const std::vector<std::string> &map)
{
    static size_t frameCounter = 0;
    std::unique_ptr<sf::Sprite> playerSprite;

    const float tileWidth = static_cast<float>(this->_window->getSize().x) /
                            static_cast<float>(map[0].size());
    const float tileHeight = static_cast<float>(this->_window->getSize().y) /
                             static_cast<float>(map.size());

    const size_t runFrame = frameCounter % this->_playerRun.size();
    const size_t flightFrame = frameCounter % this->_playerFlight.size();
    const size_t dieFrame = frameCounter % this->_playerDie.size();

    if (player.getPosY() > 0) {
        playerSprite = std::move(this->_playerFlight[flightFrame]);
    } else {
        playerSprite = std::move(this->_playerRun[runFrame]);
    }
    playerSprite->setPosition(
        player.getPosX() * tileWidth, player.getPosY() * tileHeight);
    playerSprite->setScale(tileWidth / playerSprite->getLocalBounds().width,
        tileHeight / playerSprite->getLocalBounds().height);
    this->_window->draw(*playerSprite);

    frameCounter += 1;

    if (player.getPosY() > 0) {
        this->_playerFlight[flightFrame] = std::move(playerSprite);
    } else {
        this->_playerRun[runFrame] = std::move(playerSprite);
    }
}
