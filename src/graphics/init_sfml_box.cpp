/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** init_sfml_box
*/
#include "sfml.hpp"

void Sfml::init_lib_box(SfmlBox &box, int index, char side)
{
    sf::Vector2f pos(50, index + 400);
    sf::Vector2f size(350, 90);

    if (side == 'l') {
        box.setTextPadding(26, 150);
        box.setVector(pos, size, 23);
        box.setTextColor(sf::Color::White);
        box.setBackColorRGB(13, 90, 88);
    }
    if (side == 'r') {
        pos.x = 1500;
        box.setTextPadding(26, 150);
        box.setVector(pos, size, 23);
        box.setBackColorRGB(13, 90, 88);
        box.setTextColor(sf::Color::White);
    }
}

void Sfml::init_sfml_box(std::map<int, std::string> &graph, std::map<int, std::string> &game)
{
    gm = game;
    gh = graph;
    SfmlBox objBox;
    int bound = 0;

    if (game.size() != gameBox.size()) {
        for (int i = 1; i < game.size() + 1; i++, bound += 100) {
            this->init_lib_box(objBox, bound, 'l');
            objBox.setValue(this->getLibName(game[i]), font);
            gameBox.push_back(objBox);
        }
    }
    bound = 0;
    if (graph.size() != libBox.size()) {
        for (int i = 1; i < graph.size() + 1; i++, bound += 100) {
            this->init_lib_box(objBox, bound, 'r');
            objBox.setValue(this->getLibName(graph[i]), font);
            libBox.push_back(objBox);
        }
    }
}

void Sfml::loadResources()
{
    for (int i = 1; i < gh.size() + 1; i++) {
        if (this->getLibName(gh[i]) == "sfml" && libIndex < 0) {
            libIndex = i - 1;
            break;
        }
    }
}

bool Sfml::isSpriteHover(sf::Sprite &sprite, sf::RenderWindow &window)
{
    float a;
    float b;
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    sf::FloatRect rect = sprite.getGlobalBounds();
    a = pos.x;
    b = pos.y;
    return rect.contains(sf::Vector2f(a,b));
}

void Sfml::init_game_screen()
{
    sf::Vector2f gm_pos(48, 98);
    sf::Vector2f gm_size(1682, 534);
    sf::Vector2f scr_pos(1400, 98);
    sf::Vector2f scr_size(300, 464);
    score_screen.setVector(scr_pos, scr_size, 21);
    score_screen.setBackColorRGB(4, 51, 50);
    game_screen.setVector(gm_pos, gm_size, 24);
    game_screen.setBackColorRGB(4, 51, 50);
}

void Sfml::init_name_input()
{
    input.setVector(sf::Vector2f(800, 450), sf::Vector2f(400, 90), 49, font);
    input.setBackColor(13, 90, 88);
    input.setTextColor(255, 255, 255);
}

void Sfml::input_event(sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed &&
        input.isHover(event.mouseButton.x, event.mouseButton.y)) {
        input.setBackColor(4, 51, 50);
        input.setFocus(true);
    } else if (event.type == sf::Event::MouseButtonPressed &&
        input.isHover(event.mouseButton.x, event.mouseButton.y) == false) {
        input.setBackColor(13, 90, 88);
        input.setFocus(false);
    }
    if (event.type == event.TextEntered) {
        char c = event.text.unicode;
        if (c == '\b') {
            input.deleteChar();
        } else {
            input.addChar(c);
        }
    }
}
