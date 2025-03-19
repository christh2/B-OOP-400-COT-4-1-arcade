/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** grow_snake
*/
#include "snake.hpp"

char Snake::free_direction(std::pair<int,int> ltsPoint)
{
    int x = ltsPoint.first;
    int y = ltsPoint.second;

    // right
    if (x + 1 < map[y].length() && (map[y].at(x + 1) == ' ')
    && snk_dir != arcade::Direction::RIGHT) {
        return 'r';
    }
    // left
    if (x - 1 >= 0 && (map[y].at(x - 1) == ' ')
    && snk_dir != arcade::Direction::LEFT) {
        return 'l';
    }
    // up
    if (y - 1 >= 0 && (map[y - 1].at(x) == ' ') &&
    snk_dir != arcade::Direction::TOP) {
        return 'u';
    }
    // down
    if (y + 1 <= 119 && (map[y + 1].at(x) == ' ')
    && snk_dir != arcade::Direction::DOWN) {
        return 'd';
    }
    return 'd';
}

void Snake::grow_snake(std::pair<int,int> point, std::pair<int,int> empty)
{
    char c = 0;
    int size = snake_suit.size();
    std::pair<int,int> ltsPoint;
    std::pair<int,int> temp_space;

    if (map[point.second].at(point.first) != '*') {
        // std::exit(84);
        return;
    }
    if (snake_suit.empty()) {
        c = this->free_direction(snake_pos);
        this->pushElement(snake_pos, c);
    } else {
        snake_suit.push(empty);
    }
    this->generate_random_ball();
    score += 1;
}

void Snake::pushElement(std::pair<int,int> lts, char c)
{
    std::pair<int,int> newPoint;

    if (c == 'r') {
        newPoint = std::make_pair(lts.first + 1, lts.second);
        snake_suit.push(newPoint);
    } if (c == 'l') {
        newPoint = std::make_pair(lts.first - 1, lts.second);
        snake_suit.push(newPoint);
    } if (c == 'u') {
        newPoint = std::make_pair(lts.first, lts.second - 1);
        snake_suit.push(newPoint);
    } if (c == 'd') {
        newPoint = std::make_pair(lts.first, lts.second + 1);
        snake_suit.push(newPoint);
    }
}

void Snake::check_self_collide()
{
    bool in = false;
    int size = snake_suit.size();
    std::pair<int,int> point;

    for (int i = 0; i < size; i++) {
        point = snake_suit.front();
        snake_suit.pop();
        if (point == snake_pos)
            in = true;
        snake_suit.push(point);
    }
    over = false;
}

// random ball

int Snake::random_number(int min, int max)
{
    int r = min + (std::rand() % (max - min));
    return r;
}

void Snake::generate_random_ball()
{
    std::pair<int,int> ball_pos;

    ball_pos = std::make_pair(this->random_number(0, 119), this->random_number(0, 32));

    while (this->inSnakeSuit(ball_pos)) {
        ball_pos = std::make_pair(this->random_number(0, 119), this->random_number(0, 32));
    }
    map[ball_pos.second].at(ball_pos.first) = '*';
}
