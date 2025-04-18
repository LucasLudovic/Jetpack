//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Display.cpp
//

#include "Display.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

client::Display::Display()
{
    std::cout << "Init display" << std::endl;
    this->_window =
        std::make_unique<sf::RenderWindow>(sf::VideoMode({1920, 1080}), "");
    if (!this->_window)
        throw DisplayError("Unable to render a window");
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

void client::Display::_loadAssets()
{
    std::cout << "Loading assets" << std::endl;
    this->_font = std::make_unique<sf::Font>();
    this->_font->loadFromFile(
        "./assets/fonts/JetBrainsMonoNerdFont-Medium.ttf");
    if (this->_font == nullptr)
        throw DisplayError("Can't load the font");

    this->_loadBackgroundAsset();
    this->_loadCoinAssets();
    this->_loadPlayerAssets();
    this->_loadLaserAssets();
    std::cout << "Done loading assets" << std::endl;
}

void client::Display::_loadBackgroundAsset()
{
    if (!this->_backgroundTexture.loadFromFile("assets/background1.png")) {
        throw DisplayError("Unable to load backgroundTexture");
    }
    this->_backgroundSprite.setTexture(this->_backgroundTexture);
}

void client::Display::_loadCoinAssets()
{
    const int height = 67;
    const int width = 75;

    if (!this->_coinTexture.loadFromFile("assets/coins_sprite_sheet1.png")) {
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
    if (!this->_playerTexture.loadFromFile(
            "assets/player_sprite_sheet1.png")) {
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
    const int rowIndex = 1;

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
    const int rowIndex = 3;

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
    // this->_startX = player.getPosX();
    this->_startX = player.getPosX() - (this->_endX - this->_startX) / 2.0;
    this->_endX = this->_startX + 10;

    this->_window->clear();
    this->_drawBackground();
    this->_drawProps(player, map);
    this->_drawPlayer(player, map);
    this->_drawAth(player);
    this->_window->display();
}

void client::Display::_drawAth(const Player &player)
{
    sf::Text text;
    text.setFont(*this->_font);
    text.setCharacterSize(24);

    std::stringstream stream;
    if (player.getPlayerAlive()) {
        stream << "SCORE: " << player.getScore()
               << "\n";
    } else {
        stream << "DEAD\n";
        stream << "FINAL SCORE: " << player.getScore()
               << "\n";
    }

    text.setString(stream.str());
    text.setPosition(20, 20);
    this->_window->draw(text);
}

void client::Display::_drawBackground()
{
    sf::Transform t1;
    sf::Transform t2;

    const float windowWidth = this->_window->getSize().x;
    const float windowHeight = this->_window->getSize().y;
    const float scale = windowHeight / this->_backgroundTexture.getSize().y;

    this->_backgroundSprite.setScale(scale, scale);

    const float backgroundWidth = this->_backgroundTexture.getSize().x * scale;
    const float tileW = windowWidth / (this->_endX - this->_startX - 1);

    float offset = this->_startX * tileW;

    while (offset >= backgroundWidth) {
        offset -= backgroundWidth;
    }
    while (offset < 0) {
        offset += backgroundWidth;
    }

    offset *= -1;
    t1.translate(offset, 0);
    t2.translate(offset + backgroundWidth, 0);

    this->_window->draw(this->_backgroundSprite, t1);
    this->_window->draw(this->_backgroundSprite, t2);
}

void client::Display::_drawProps(
    const Player &player, const std::vector<std::string> &map)
{
    static size_t frameCounter = 0;

    const float width = static_cast<float>(this->_window->getSize().x) /
                        (this->_endX - this->_startX + 1);
    const float height = static_cast<float>(this->_window->getSize().y) /
                         static_cast<float>(map.size());
    const size_t coinFrame = frameCounter % _coin.size();
    const size_t laserFrame = frameCounter % _laser.size();

    for (size_t y = 0; y < map.size(); y += 1) {
        for (size_t x = this->_startX; x < this->_endX; x += 1) {
            if (x >= map[y].size())
                break;
            char tile = map[y][x];
            sf::Vector2f position((x - this->_startX) * width, y * height);

            if (tile == 'c') {
                auto &sprite = *this->_coin[coinFrame];
                sprite.setPosition(position);
                this->_window->draw(sprite);
            }
            if (tile == 'e') {
                auto &sprite = *this->_laser[laserFrame];
                sprite.setPosition(position);
                this->_window->draw(sprite);
            }
        }
    }
    frameCounter += 1;
}

void client::Display::_drawPlayer(
    const Player &player, const std::vector<std::string> &map)
{
    static size_t frameCounter = 0;
    std::unique_ptr<sf::Sprite> playerSprite;
    static int frameDelay = 0;

    const float tileWidth = static_cast<float>(this->_window->getSize().x) /
                            static_cast<float>(map[0].size());
    const float tileHeight = static_cast<float>(this->_window->getSize().y) /
                             static_cast<float>(map.size());

    frameDelay++;
    if (frameDelay >= 6) {
        frameCounter++;
        frameDelay = 0;
    }

    const size_t runFrame = frameCounter % this->_playerRun.size();
    const size_t flightFrame = frameCounter % this->_playerFlight.size();
    const size_t dieFrame = frameCounter % this->_playerDie.size();
    float playerStartX = this->_window->getSize().x / 2.0;

    if (player.getPosY() > 0 && player.getPlayerAlive()) {
        playerSprite = std::move(this->_playerFlight[flightFrame]);
    } else if (player.getPlayerAlive()) {
        playerSprite = std::move(this->_playerRun[runFrame]);
    } else {
        playerSprite = std::move(this->_playerDie[dieFrame]);
    }
    playerSprite->setPosition(playerStartX - (tileWidth / 2),
        (map.size() - 1 - player.getPosY()) * tileHeight);
    this->_window->draw(*playerSprite);

    if (player.getPosY() > 0 && player.getPlayerAlive()) {
        this->_playerFlight[flightFrame] = std::move(playerSprite);
    } else if (player.getPlayerAlive()) {
        this->_playerRun[runFrame] = std::move(playerSprite);
    } else {
        this->_playerDie[dieFrame] = std::move(playerSprite);
    }
}
