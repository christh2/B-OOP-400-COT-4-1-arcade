/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** pacman
*/
#include "../../Arcade.hpp"
#ifndef PACMAN_HPP_
    #define PACMAN_HPP_

class Pacman : public arcade::IGame {
    public:
        Pacman();
        ~Pacman();
        void setEvents(arcade::Keyboard key);
        void run();
        bool isOver();
        void reset();
        std::vector<std::string> getMap();
        int getScore();
        void setUsername(std::string name);
    private:
        // private variables
        std::vector<std::string> map;
        std::vector<std::string> cpyMap;
        bool over;
        std::pair<int,int> pac_pos;
        arcade::Direction pac_dir;
        int score;
        // private methods
        void loadMap(std::string mapFile);
        void move_up();
        void move_down();
        void move_left();
        void move_right();
        void pacman_moves();
        // void refreshMap();
};

#endif /* !PACMAN_HPP_ */
