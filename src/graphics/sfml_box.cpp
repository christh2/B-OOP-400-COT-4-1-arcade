/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** sfml_box
*/
#include "sfml_box.hpp"

SfmlBox::SfmlBox()
{
    box.setSize(sf::Vector2f{50,50});
    box.setFillColor(sf::Color::Blue);   
    boxText.setFillColor(sf::Color::White);
    top = 0;
    left = 0;
}

SfmlBox::~SfmlBox()
{
    
}

void SfmlBox::setVector(sf::Vector2f pos, sf::Vector2f siz, int charSize)
{
    box.setSize(siz);
    box.setPosition(pos);
    boxText.setPosition(sf::Vector2f{pos.x + left, pos.y + top});
    boxText.setCharacterSize(charSize);
}

void SfmlBox::setValue(std::string str, sf::Font &font)
{
    boxText.setString(str);
    boxText.setFont(font);
}

void SfmlBox::setBackColorRGB(int _red, int _green, int _blue)
{
    sf::Color color(_red, _green, _blue);
    // color.r = _red;
    // color.g = _green;
    // color.b = _blue;
    box.setFillColor(color);
}

void SfmlBox::setBackColor(sf::Color col)
{
    box.setFillColor(col);
}

void SfmlBox::setTextColor(sf::Color col)
{
    boxText.setFillColor(col);
}

void SfmlBox::setTextColorRGB(int _red, int _green, int _blue)
{
    sf::Color col(_red, _green, _blue);
    boxText.setFillColor(col);
}

void SfmlBox::setTextPadding(int tp, int lt)
{
    top = tp;
    left = lt;
    sf::Vector2f pos = box.getPosition();
    // boxText.setPosition(sf::Vector2f{pos.x + left, pos.y + top});
}

void SfmlBox::display(sf::RenderWindow &window)
{
    window.draw(box);
    window.draw(boxText);
}

bool SfmlBox::isHover(sf::RenderWindow &win)
{
    sf::Vector2i pos = sf::Mouse::getPosition(win);
    sf::FloatRect rect = box.getGlobalBounds();
    float a = pos.x;
    float b = pos.y;
    return rect.contains(sf::Vector2f{a, b});
}

void SfmlBox::scale(sf::Vector2f scaleV)
{
    boxText.setScale(scaleV);
    box.setScale(scaleV);
}

// Sfml input

SfmlInput::SfmlInput()
{
    box_data = "";
    focus = false;
}

SfmlInput::~SfmlInput()
{
}

void SfmlInput::setVector(sf::Vector2f pos, sf::Vector2f siz, int charSize, sf::Font &fontdata)
{
    box.setPosition(pos);
    box.setSize(siz);
    boxText.setFont(fontdata);
    boxText.setCharacterSize(charSize);
    boxText.setFillColor(sf::Color::White);
    boxText.setPosition(pos);
    box.setFillColor(sf::Color::Black);
}

void SfmlInput::addChar(char c)
{
    if (!focus)
        return;
    std::string str = box_data;
    str += c;
    boxText.setString(str);
    sf::FloatRect textRect = boxText.getLocalBounds();

    if (textRect.width >= box.getSize().x)
        return;
    box_data += c;
    boxText.setString(box_data);
}

void SfmlInput::deleteChar()
{
    if (box_data.empty() || !focus)
        return;
    std::size_t pos = box_data.length() - 1;
    box_data.erase(pos, 1);
    boxText.setString(box_data);
}

void SfmlInput::setTextColor(int r, int g, int b)
{
    boxText.setFillColor(sf::Color(r, g, b));
}

void SfmlInput::setBackColor(int r, int g, int b)
{
    box.setFillColor(sf::Color(r, g, b));
}

void SfmlInput::setFocus(bool isFocus)
{
    focus = isFocus;
}

void SfmlInput::display(sf::RenderWindow &win)
{
    win.draw(box);
    win.draw(boxText);
}

bool SfmlInput::isHover(int x, int y)
{
    sf::FloatRect rect = box.getGlobalBounds();
    return rect.contains(x, y);
}

std::string SfmlInput::getData()
{
    return box_data;
}
