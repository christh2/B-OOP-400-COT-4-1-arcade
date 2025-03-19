/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** ncurse
*/
#include <ncurses.h>
#include "../../Arcade.hpp"
#ifndef NCURSE_HPP_
    #define NCURSE_HPP_
    #define white_on_red 3
    #define white_on_green 4

class Ncurse: public arcade::IGraphic {

    public:
        enum menu_state {
            MENU_GAMES,
            MENU_CHOICE,
            MENU_LIBS,
            MENU_NONE
        };
        Ncurse();
        ~Ncurse();
        void launch_display(std::vector<std::string> map, arcade::graphic_state &state,
        std::map<int, std::string>& graphic_libs, std::map<int, std::string> &games_lib);
        arcade::Keyboard getUserInput(std::map<int, std::string> &graphlist, std::map<int, std::string> &gamelist, arcade::graphic_state &state);
        void close_win();
        std::string getUsername();
        void setScore(int score);
    private:
        void loadResources();
        void displayMap(std::vector<std::string> map);
        bool open_state;
        WINDOW *window;
        WINDOW *dash;
        WINDOW *menu_mid;
        WINDOW *menu_graphics;
        WINDOW *menu_enter;
        WINDOW *menu_games;
        WINDOW *input_area;
        std::string name;
        int disp_score;
        menu_state st;
        int game_option;
        int choice_option;
        int lib_option;
        std::map<int, std::pair<std::string, std::string>> gh;
        std::map<int, std::pair<std::string, std::string>> gm;

        std::string *menu_str;
        void init_menu();
        void load_menu_str();
        void display_menu(std::map<int, std::string> &graph, std::map<int, std::string> &game);
        void clear_console();
        std::string getLibName(std::string lib);
        void libFilter(std::map<int, std::string> &graph, std::map<int, std::string> &game);

        // event
        arcade::Keyboard menu_event(int touch, std::map<int, std::string> &graph, std::map<int, std::string> &game, arcade::graphic_state &state);
        void menu_right_event();
        void menu_left_event();
        void menu_up_event();
        void menu_down_event();
        void display_menu_state();
        void display_menu_enter();
        void state_border();
        arcade::Keyboard enter_event(std::map<int, std::string> &graph, std::map<int, std::string> &game);
        void getName(int c);
        bool isValid(char c);
};

#endif /* !NCURSE_HPP_ */
