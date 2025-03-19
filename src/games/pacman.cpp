/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** pacman
*/
#include "pacman.hpp"


extern "C" {
    arcade::IGame *creater() {
        return new Pacman();
    }
    std::string get_type() {
        return "game";
    }
}

Pacman::Pacman()
{
    over = false;
    this->loadMap("src/games/pac.txt");
    cpyMap = map;
    pac_dir = arcade::Direction::RIGHT;
    score = 0;
}

Pacman::~Pacman()
{

}

void Pacman::setEvents(arcade::Keyboard key)
{
    if (key == arcade::Keyboard::keyDown) {
        pac_dir = arcade::Direction::DOWN;
        return;
    }
    if (key == arcade::Keyboard::KeyUp) {
        pac_dir = arcade::Direction::TOP;
        return;
    }
    if (key == arcade::Keyboard::keyLeft) {
        pac_dir = arcade::Direction::LEFT;
        return;
    }
    if (key == arcade::Keyboard::keyRight) {
        pac_dir = arcade::Direction::RIGHT;
        return;
    }
}

void Pacman::run()
{
    this->pacman_moves();
}

bool Pacman::isOver()
{
    return over;
}

void Pacman::reset()
{

}

std::vector<std::string> Pacman::getMap()
{
    return map;
}

// private methods
void Pacman::loadMap(std::string mapFile)
{
    std::fstream file(mapFile);
    std::string line_buffer;
    std::size_t pos;

    if (!file.is_open()) {
        std::cerr << "Fail to open file\n";
        std::exit(84);
    }
    while (std::getline(file, line_buffer)) {
        map.push_back(line_buffer);
    }
    file.close();
    for (int i = 0; i < map.size(); i++) {
        if ((pos = map[i].find('C')) != std::string::npos) {
            pac_pos = std::make_pair((int) pos, i);
            break;
        }
    }
}

int Pacman::getScore()
{
    return score;
}

void Pacman::setUsername(std::string name)
{
    
}
// void Pacman::refreshMap()
// {
//     map[pac_pos.second].at(pac_pos.first) = 'P';
// }

// int main()
// {
//     Pacman pc;
// }