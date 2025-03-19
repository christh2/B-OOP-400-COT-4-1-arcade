/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** pacman_moves
*/
#include "pacman.hpp"

void Pacman::move_up()
{
    if (pac_pos.second - 1 < 0)
        return;
    if (map[pac_pos.second - 1].at(pac_pos.first) == ' ' ||
        map[pac_pos.second - 1].at(pac_pos.first) == '.') {
        if (map[pac_pos.second - 1].at(pac_pos.first) == '.')
            score++;
        pac_pos.second--;
        map[pac_pos.second + 1].at(pac_pos.first) = ' ';
    }
}

void Pacman::move_down()
{
    if (pac_pos.second + 1 >= map.size())
        return;
    if (map[pac_pos.second + 1].at(pac_pos.first) == ' ' ||
        map[pac_pos.second + 1].at(pac_pos.first) == '.') {
        if (map[pac_pos.second + 1].at(pac_pos.first) == '.')
            score++;
        pac_pos.second++;
        map[pac_pos.second - 1].at(pac_pos.first) = ' ';
    }
}

void Pacman::move_left()
{
    if (pac_pos.first - 1 < 0)
        return;
    if (map[pac_pos.second].at(pac_pos.first - 1) == ' ' ||
        map[pac_pos.second].at(pac_pos.first - 1) == '.' ) {
        if (map[pac_pos.second].at(pac_pos.first - 1) == '.' )
            score++;
        pac_pos.first--;
        map[pac_pos.second].at(pac_pos.first + 1) = ' ';
    }
}

void Pacman::move_right()
{
    if (pac_pos.first + 1 >= map[pac_pos.second].length())
        return;
    if (map[pac_pos.second].at(pac_pos.first + 1) == ' ' ||
        map[pac_pos.second].at(pac_pos.first + 1) == '.') {
        if (map[pac_pos.second].at(pac_pos.first + 1) == '.')
            score++;
        pac_pos.first++;
        map[pac_pos.second].at(pac_pos.first - 1) = ' ';
    }
}
void Pacman::pacman_moves()
{
    if (pac_dir == arcade::Direction::DOWN)
        this->move_down();
    if (pac_dir == arcade::Direction::TOP)
        this->move_up();
    if (pac_dir == arcade::Direction::LEFT)
        this->move_left();
    if (pac_dir == arcade::Direction::RIGHT)
        this->move_right();
    map[pac_pos.second].at(pac_pos.first) = 'C';
}
