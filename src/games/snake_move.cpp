/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** snake_move
*/
#include "snake.hpp"

void Snake::move_snake_up()
{
    std::pair<int,int> empty_place;
    int size = snake_suit.size();
    std::pair<int,int> snk_elem;

    if (snake_pos.second - 1 < 0) {
        over = true;
        return;
    }
    empty_place = snake_pos;
    snake_pos.second -= 1;

    for (int i = 0; i < size; i++) {
        snk_elem = snake_suit.front();
        snk_elem = empty_place;
        empty_place = snake_suit.front();
        snake_suit.pop();
        snake_suit.push(snk_elem);
    }
    this->grow_snake(snake_pos, empty_place);
}

void Snake::move_snake_down()
{
    std::pair<int,int> empty_place;
    int size = snake_suit.size();
    std::pair<int,int> snk_elem;

    if (snake_pos.second + 1 >= map_line) {
        over = true;
        return;
    }
    empty_place = snake_pos;
    snake_pos.second += 1;
    // if (snake_suit.empty())
    //     return;

    for (int i = 0; i < size; i++) {
        snk_elem = snake_suit.front();
        snk_elem = empty_place;
        empty_place = snake_suit.front();
        snake_suit.pop();
        snake_suit.push(snk_elem);
    }
    this->grow_snake(snake_pos, empty_place);
}

void Snake::move_snake_left()
{
    std::pair<int,int> empty_place;
    int size = snake_suit.size();
    std::pair<int,int> snk_elem;

    if (snake_pos.first - 1 < 0) {
        over = true;
        return;
    }
    empty_place = snake_pos;
    snake_pos.first -= 1;
    // if (snake_suit.empty())
    //     return;

    for (int i = 0; i < size; i++) {
        snk_elem = snake_suit.front();
        snk_elem = empty_place;
        empty_place = snake_suit.front();
        snake_suit.pop();
        snake_suit.push(snk_elem);
    }
    this->grow_snake(snake_pos, empty_place);
}

void Snake::move_snake_right()
{
    std::pair<int,int> empty_place;
    int size = snake_suit.size();
    std::pair<int,int> snk_elem;

    if (snake_pos.first + 1 > 119) {
        over = true;
        return;
    }
    empty_place = snake_pos;
    snake_pos.first += 1;
    for (int i = 0; i < size; i++) {
        snk_elem = empty_place;
        empty_place = snake_suit.front();
        snake_suit.pop();
        snake_suit.push(snk_elem);
    }
    this->grow_snake(snake_pos, empty_place);
}

void Snake::move_snake()
{
    bool move_done = false;

    if (snk_dir == arcade::Direction::DOWN) {
        this->move_snake_down();
        move_done = true;
    }
    if (snk_dir == arcade::Direction::TOP) {
        this->move_snake_up();
        move_done = true;
    }
    if (snk_dir == arcade::Direction::LEFT) {
        this->move_snake_left();
        move_done = true;
    }
    if (snk_dir == arcade::Direction::RIGHT) {
        this->move_snake_right();
        move_done = true;
    }
    this->refreshMap();
}

// Map

bool Snake::inSnakeSuit(std::pair<int,int> cod)
{
    std::pair<int,int> temp_space;
    int size = snake_suit.size();
    bool in = false;

    if (snake_pos == cod)
        return true;

    for (int i = 0; i < size; i++) {
        temp_space = snake_suit.front();
        snake_suit.pop();
        if (temp_space == cod) {
            in = true;
        }
        snake_suit.push(temp_space);
    }
    return in;
}

void Snake::refresh_position(int x, int y)
{
    if (map[y].at(x) == 'O'
    && this->inSnakeSuit(std::make_pair(x,y)) == false) {
        map[y].at(x) = ' ';
    }
}

void Snake::refreshMap()
{
    int size = snake_suit.size();
    std::pair<int,int> temp_space;

    for (int j = 0; j < map_line; j++) {
        for (int i = 0; i < map[j].length(); i++) {
            this->refresh_position(i, j);
        }
    }
    if (!this->canMap(snake_pos)) {
        over = true;
        return;
    }
    map[snake_pos.second].at(snake_pos.first) = 'O';
    for (int i = 0; i < size; i++) {
        temp_space = snake_suit.front();
        snake_suit.pop();
        if (!this->canMap(temp_space)) {
            over = true;
            return;
        }
        map[temp_space.second].at(temp_space.first) = 'O';
        snake_suit.push(temp_space);
    }
}

bool Snake::canMap(std::pair<int,int> point)
{
    if (point.first < 0 || point.second >= 120 ||
    point.second < 0 || point.first >= map[point.second].length())
        return false;
    return true;
}
