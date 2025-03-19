/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** snake
*/

#include "snake.hpp"

extern "C" {
    arcade::IGame* creater()
    {
        arcade::IGame *gm = new Snake();
        return gm;
    }
    std::string get_type()
    {
        return "game";
    }
}

Snake::Snake()
{
    map_line = 38;
    this->generateMap();
    this->init_game();
    over = false;
    score = 0;
}

void Snake::generateMap()
{
    std::string str;
    for (int i = 0; i < map_line; i++) {
        str = "";
        for (int j = 0; j < 120; j++) {
            str += " ";
        }
        map.push_back(str);
    }
}

Snake::~Snake()
{
}

void Snake::delete_snake_suit()
{
    int size = snake_suit.size();

    for (int i = 0; i < size; i++) {
        snake_suit.pop();
    }
}

void Snake::init_game()
{
    bool fruit = false;
    over = false;
    map[11].at(59) = 'O';
    for (int i = 0; i < map.size(); i++) {
        if (map[i].find('*') != std::string::npos) {
            fruit = true;
            break;
        }
    }
    if (!fruit)
        map[11].at(90) = '*';
    snake_pos = std::make_pair(59, 11);
    this->delete_snake_suit();
    snk_dir = arcade::Direction::RIGHT;
    for (int i = 1; i < 4; i++) {
        snake_suit.push(std::make_pair(snake_pos.first + i, snake_pos.second));
        map[snake_pos.second].at(snake_pos.first + i) = 'O';
    }
}

void Snake::setEvents(arcade::Keyboard key)
{
    if (key == arcade::Keyboard::keyRight
    && snk_dir != arcade::Direction::LEFT) {
        snk_dir = arcade::Direction::RIGHT;
    }
    if (key == arcade::Keyboard::keyLeft
    && snk_dir != arcade::Direction::RIGHT ) {
        snk_dir = arcade::Direction::LEFT;
    }
    if (key == arcade::Keyboard::keyDown
    && snk_dir != arcade::Direction::TOP) {
        snk_dir = arcade::Direction::DOWN;
    }
    if (key == arcade::Keyboard::KeyUp
    && snk_dir != arcade::Direction::DOWN) {
        snk_dir = arcade::Direction::TOP;
    }
}

void Snake::run()
{
    this->move_snake();
    this->check_self_collide();
}

bool Snake::isOver()
{
    return over;
}

void Snake::reset()
{
    over = false;
    init_game();
}

std::vector<std::string> Snake::getMap()
{
    return map;
}

void Snake::setUsername(std::string name)
{

}

int Snake::getScore()
{
    return score;
}
