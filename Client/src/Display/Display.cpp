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

void client::Display::drawEntity(const std::string &texturePath, float posx,
    float posy, float scalex, float scaley)
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

void client::Display::drawText(const std::string &str, float posx, float posy)
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

std::vector<client::Inputs> &client::Display::getEvents()
{
    sf::Event event;
    this->_events.clear();

    const std::map<client::keys, sf::Keyboard::Key> code{
        {keys::KEY_A, sf::Keyboard::Key::A},
        {keys::KEY_B, sf::Keyboard::Key::B},
        {keys::KEY_C, sf::Keyboard::Key::C},
        {keys::KEY_D, sf::Keyboard::Key::D},
        {keys::KEY_E, sf::Keyboard::Key::E},
        {keys::KEY_F, sf::Keyboard::Key::F},
        {keys::KEY_G, sf::Keyboard::Key::G},
        {keys::KEY_H, sf::Keyboard::Key::H},
        {keys::KEY_I, sf::Keyboard::Key::I},
        {keys::KEY_J, sf::Keyboard::Key::J},
        {keys::KEY_K, sf::Keyboard::Key::K},
        {keys::KEY_L, sf::Keyboard::Key::L},
        {keys::KEY_M, sf::Keyboard::Key::M},
        {keys::KEY_N, sf::Keyboard::Key::N},
        {keys::KEY_O, sf::Keyboard::Key::O},
        {keys::KEY_P, sf::Keyboard::Key::P},
        {keys::KEY_Q, sf::Keyboard::Key::Q},
        {keys::KEY_R, sf::Keyboard::Key::R},
        {keys::KEY_S, sf::Keyboard::Key::S},
        {keys::KEY_T, sf::Keyboard::Key::T},
        {keys::KEY_U, sf::Keyboard::Key::U},
        {keys::KEY_V, sf::Keyboard::Key::V},
        {keys::KEY_W, sf::Keyboard::Key::W},
        {keys::KEY_X, sf::Keyboard::Key::X},
        {keys::KEY_Y, sf::Keyboard::Key::Y},
        {keys::KEY_Z, sf::Keyboard::Key::Z},
        {keys::KEY_0, sf::Keyboard::Key::Num0},
        {keys::KEY_1, sf::Keyboard::Key::Num1},
        {keys::KEY_2, sf::Keyboard::Key::Num2},
        {keys::KEY_3, sf::Keyboard::Key::Num3},
        {keys::KEY_4, sf::Keyboard::Key::Num4},
        {keys::KEY_5, sf::Keyboard::Key::Num5},
        {keys::KEY_6, sf::Keyboard::Key::Num6},
        {keys::KEY_7, sf::Keyboard::Key::Num7},
        {keys::KEY_8, sf::Keyboard::Key::Num8},
        {keys::KEY_9, sf::Keyboard::Key::Num9},
        {keys::SPECIAL_KEY_SPACE, sf::Keyboard::Key::Space},
        {keys::SPECIAL_KEY_BACKSPACE, sf::Keyboard::Key::BackSpace},
        {keys::SPECIAL_KEY_ENTER, sf::Keyboard::Key::Enter},
        {keys::ARROW_LEFT, sf::Keyboard::Left},
        {keys::ARROW_RIGHT, sf::Keyboard::Right},
        {keys::ARROW_DOWN, sf::Keyboard::Down},
        {keys::ARROW_UP, sf::Keyboard::Up}};

    while (this->_window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyReleased: {
                for (auto it : code)
                    if (event.key.code == it.second) {
                        client::Inputs ev;
                        ev.key = it.first;
                        ev.state = state::RELEASED;
                        this->_events.push_back(ev);
                        break;
                    }
                break;
            }
            case sf::Event::KeyPressed: {
                for (auto it : code)
                    if (event.key.code == it.second) {
                        client::Inputs ev;
                        ev.key = it.first;
                        ev.state = state::PRESSED;
                        this->_events.push_back(ev);
                        break;
                    }
                break;
            }
            case sf::Event::Closed: {
                client::Inputs ev;
                ev.key = keys::CLOSE;
                ev.state = state::PRESSED;
                this->_events.push_back(ev);
                break;
            }
            default:
                break;
        }
    }
    return this->_events;
}

void client::Display::render()
{
    this->_window->display();
}

void client::Display::clear()
{
    this->_window->clear();
}
