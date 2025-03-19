/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** sfml_box
*/
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#ifndef SFML_BOX_HPP_
    #define SFML_BOX_HPP_

class SfmlBox {
    public:
        SfmlBox();
        ~SfmlBox();
        void setVector(sf::Vector2f pos, sf::Vector2f siz, int charSize);
        void setValue(std::string str, sf::Font &font);
        void setBackColorRGB(int _red, int _green, int _blue);
        void setBackColor(sf::Color col);
        void setTextColor(sf::Color col);
        void setTextColorRGB(int _red, int _green, int _blue);
        void setTextPadding(int tp, int lt);
        void display(sf::RenderWindow &window);
        bool isHover(sf::RenderWindow &win);
        void scale(sf::Vector2f scaleV);
    private:
        sf::RectangleShape box;
        sf::Text boxText;
        int top;
        int left;
};

class SfmlInput {
    public:
        SfmlInput();
        ~SfmlInput();
        void setVector(sf::Vector2f pos, sf::Vector2f siz, int charSize, sf::Font &fontdata);
        void addChar(char c);
        void deleteChar();
        void setTextColor(int r, int g, int b);
        void setBackColor(int r, int g, int b);
        void setFocus(bool isFocus);
        void display(sf::RenderWindow &win);
        bool isHover(int x, int y);
        std::string getData();
    private:
        sf::RectangleShape box;
        sf::Text boxText;
        std::string box_data;
        bool focus;
};

#endif /* !SFML_BOX_HPP_ */
