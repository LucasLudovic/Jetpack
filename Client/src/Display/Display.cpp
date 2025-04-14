//
// EPITECH PROJECT, 2025
// Jetpack
// File description:
// Display.cpp
//

#include "Display.hpp"
#include "Inputs/Inputs.hpp"
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

    const std::map<client::ev_keys, sf::Keyboard::Key> code{
        {ev_keys::KEY_A, sf::Keyboard::Key::A},
        {ev_keys::KEY_B, sf::Keyboard::Key::B},
        {ev_keys::KEY_C, sf::Keyboard::Key::C},
        {ev_keys::KEY_D, sf::Keyboard::Key::D},
        {ev_keys::KEY_E, sf::Keyboard::Key::E},
        {ev_keys::KEY_F, sf::Keyboard::Key::F},
        {ev_keys::KEY_G, sf::Keyboard::Key::G},
        {ev_keys::KEY_H, sf::Keyboard::Key::H},
        {ev_keys::KEY_I, sf::Keyboard::Key::I},
        {ev_keys::KEY_J, sf::Keyboard::Key::J},
        {ev_keys::KEY_K, sf::Keyboard::Key::K},
        {ev_keys::KEY_L, sf::Keyboard::Key::L},
        {ev_keys::KEY_M, sf::Keyboard::Key::M},
        {ev_keys::KEY_N, sf::Keyboard::Key::N},
        {ev_keys::KEY_O, sf::Keyboard::Key::O},
        {ev_keys::KEY_P, sf::Keyboard::Key::P},
        {ev_keys::KEY_Q, sf::Keyboard::Key::Q},
        {ev_keys::KEY_R, sf::Keyboard::Key::R},
        {ev_keys::KEY_S, sf::Keyboard::Key::S},
        {ev_keys::KEY_T, sf::Keyboard::Key::T},
        {ev_keys::KEY_U, sf::Keyboard::Key::U},
        {ev_keys::KEY_V, sf::Keyboard::Key::V},
        {ev_keys::KEY_W, sf::Keyboard::Key::W},
        {ev_keys::KEY_X, sf::Keyboard::Key::X},
        {ev_keys::KEY_Y, sf::Keyboard::Key::Y},
        {ev_keys::KEY_Z, sf::Keyboard::Key::Z},
        {ev_keys::KEY_0, sf::Keyboard::Key::Num0},
        {ev_keys::KEY_1, sf::Keyboard::Key::Num1},
        {ev_keys::KEY_2, sf::Keyboard::Key::Num2},
        {ev_keys::KEY_3, sf::Keyboard::Key::Num3},
        {ev_keys::KEY_4, sf::Keyboard::Key::Num4},
        {ev_keys::KEY_5, sf::Keyboard::Key::Num5},
        {ev_keys::KEY_6, sf::Keyboard::Key::Num6},
        {ev_keys::KEY_7, sf::Keyboard::Key::Num7},
        {ev_keys::KEY_8, sf::Keyboard::Key::Num8},
        {ev_keys::KEY_9, sf::Keyboard::Key::Num9},
        {ev_keys::SPECIAL_KEY_SPACE, sf::Keyboard::Key::Space},
        {ev_keys::SPECIAL_KEY_BACKSPACE, sf::Keyboard::Key::BackSpace},
        {ev_keys::SPECIAL_KEY_ENTER, sf::Keyboard::Key::Enter},
        {ev_keys::ARROW_LEFT, sf::Keyboard::Left},
        {ev_keys::ARROW_RIGHT, sf::Keyboard::Right},
        {ev_keys::ARROW_DOWN, sf::Keyboard::Down},
        {ev_keys::ARROW_UP, sf::Keyboard::Up}};

    while (this->_window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyReleased: {
                for (auto it : code)
                    if (event.key.code == it.second) {
                        client::Inputs ev;
                        ev.key = it.first;
                        ev.state = ev_state::RELEASED;
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
                        ev.state = ev_state::PRESSED;
                        this->_events.push_back(ev);
                        break;
                    }
                break;
            }
            case sf::Event::Closed: {
                client::Inputs ev;
                ev.key = ev_keys::CLOSE;
                ev.state = ev_state::PRESSED;
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
