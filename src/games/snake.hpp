/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** snake
*/

#include "../../Arcade.hpp"
#include <iostream>
#ifndef SNAKE_HPP_
    #define SNAKE_HPP_

class Snake : public arcade::IGame {
    public:
        Snake();
        ~Snake();
        void setEvents(arcade::Keyboard key);
        void run();
        bool isOver();
        void reset();
        std::vector<std::string> getMap();
        void setUsername(std::string name);
        int getScore();
    private:
        void init_game();
        int map_line;
        std::vector<std::string> map;
        std::pair<int,int> snake_pos;
        std::queue<std::pair<int,int>> snake_suit;
        bool over;
        arcade::Direction snk_dir;
        int score;

        // moves
        void move_snake();
        void move_snake_up();
        void move_snake_down();
        void move_snake_right();
        void move_snake_left();
        void refreshMap();
        void refresh_position(int x, int y);
        bool inSnakeSuit(std::pair<int,int> cod);
        //map
        void generateMap();
        void delete_snake_suit();
        bool canMap(std::pair<int,int> point);
        // grow
        void grow_snake(std::pair<int,int> point, std::pair<int,int> empty);
        char free_direction(std::pair<int,int> lstPoint);
        void pushElement(std::pair<int,int> lts, char c);

        // collide check
        void check_self_collide();

        // Generate random ball
        int random_number(int min, int max);
        void generate_random_ball();
};

#endif 
