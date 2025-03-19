/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** ncurse_event
*/
#include "ncurse.hpp"

void Ncurse::menu_right_event()
{
    if (st == MENU_LIBS) {
        choice_option = -1;
        st = MENU_GAMES;
        return;
    }
    if (st == MENU_GAMES) {
        choice_option = 0;
        st = MENU_CHOICE;
        return;
    }
    if (st == MENU_CHOICE) {
        choice_option = -1;
        st = MENU_LIBS;
        return;
    }
}

void Ncurse::menu_left_event()
{
    if (st == MENU_GAMES) {
        choice_option = -1;
        st = MENU_LIBS;
        return;
    }
    if (st == MENU_LIBS) {
        st = MENU_CHOICE;
        choice_option = 0;
        return;
    }
    if (st == MENU_CHOICE) {
        choice_option = -1;
        st = MENU_GAMES;
        return;
    }
}

void Ncurse::menu_up_event()
{
    if (st == MENU_GAMES) {
        if (game_option == 0)
            game_option = gm.size() - 1;
        else
            game_option--;
    }
    if (st == MENU_CHOICE) {
        if (choice_option == 0)
            choice_option = 2;
        else
            choice_option--;
    }
    if (st == MENU_LIBS) {
        if (lib_option == 0)
            lib_option = gh.size() - 1;
        else
            lib_option--;
    }
}

void Ncurse::menu_down_event()
{
    if (st == MENU_GAMES) {
        if (game_option == gm.size() - 1)
            game_option = 0;
        else
            game_option++;
    }
    if (st == MENU_CHOICE) {
        if (choice_option == 2)
            choice_option = 0;
        else
            choice_option++;
    }
    if (st == MENU_LIBS) {
        if (lib_option == gh.size() - 1)
            lib_option = 0;
        else
            lib_option++;
    }
}

arcade::Keyboard Ncurse::menu_event(int touch, std::map<int, std::string> &graph, std::map<int, std::string> &game, arcade::graphic_state &state)
{
    arcade::Keyboard key = arcade::Keyboard::keyNone;
    this->getName(touch);
    if (state != arcade::MENU_STATE)
        return key;
    //printw("Empty");
    if (touch == KEY_LEFT)
        this->menu_left_event();
    if (touch == KEY_RIGHT)
        this->menu_right_event();
    if (touch == KEY_UP)
        this->menu_up_event();
    if (touch == KEY_DOWN)
        this->menu_down_event();
    if (touch == '\n')
        key = this->enter_event(graph, game);
    return key;
}

void Ncurse::display_menu_state()
{
    int bound = 8;

    for (int i = 1; i < gm.size() + 1; i++, bound += 2) {
        if (i == game_option + 1) {
            wattron(menu_games ,COLOR_PAIR(2));
            mvwprintw(menu_games, i + bound, 14, "+ ");
            mvwprintw(menu_games, i + bound, 17, gm[i].first.c_str());
            wattroff(menu_games, COLOR_PAIR(2));
        } else {
            mvwprintw(menu_games, i + bound, 14, "  ");
            mvwprintw(menu_games, i + bound, 17, gm[i].first.c_str());
        }
    }
    bound = 8;
    for (int i = 1; i < gh.size() + 1; i++, bound += 2) {
        if (i == lib_option + 1) {
            wattron(menu_graphics ,COLOR_PAIR(2));
            mvwprintw(menu_graphics, i + bound, 14, "+ ");
            mvwprintw(menu_graphics, i + bound, 17, gh[i].first.c_str());
            wattroff(menu_graphics, COLOR_PAIR(2));
        } else {
            mvwprintw(menu_graphics, i + bound, 14, "  ");
            mvwprintw(menu_graphics, i + bound, 17, gh[i].first.c_str());
        }
    }
}

void Ncurse::display_menu_enter()
{
    std::string enter = "START";
    std::string quit = "QUIT";

    if (choice_option == 1) {
        wattron(menu_enter, COLOR_PAIR(white_on_green));
        mvwprintw(menu_enter, 5, 16, "  %s  ", enter.c_str());
        wattroff(menu_enter, COLOR_PAIR(white_on_green));
    } else {
        mvwprintw(menu_enter, 5, 16, "  %s  ", enter.c_str());
    }
    if (choice_option == 2) {
        wattron(menu_enter, COLOR_PAIR(white_on_red));
        mvwprintw(menu_enter, 7, 16, "   %s   ", quit.c_str());
        wattroff(menu_enter, COLOR_PAIR(white_on_red));
    } else {
        mvwprintw(menu_enter, 7, 16, "   %s   ", quit.c_str());
    }
    mvwprintw(input_area, 1, 1, "%s", name.c_str());
}

void Ncurse::state_border()
{
    if (st == MENU_GAMES) {
        wborder(menu_games, '|', '|', '-', '-', '+', '+', '+', '+');
    }
    if (st == MENU_LIBS) {
        wborder(menu_graphics, '|', '|', '-', '-', '+', '+', '+', '+');
    }
    if (st == MENU_CHOICE) {
        if (choice_option == 0)
            wborder(input_area, 0, 0, 0, 0, 0, 0, 0, 0);
        wborder(menu_enter, 0, 0, 0, 0, 0, 0, 0, 0);
    }
}

arcade::Keyboard Ncurse::enter_event(std::map<int, std::string> &graph, std::map<int, std::string> &game)
{
    if (choice_option == 1 && !name.empty()) {
        graph[1] = gh[lib_option + 1].second;
        game[1] = gm[game_option + 1].second;
        return arcade::KeyEnter;
    } else if (choice_option == 2){
        return arcade::keyQuit;
    }
    return arcade::keyNone;
}

// get lib name
std::string Ncurse::getLibName(std::string lib)
{
    std::string proto = "arcade_";
    std::size_t pos = lib.find(proto);
    std::size_t st_pos = pos + proto.length();
    std::size_t end_pos = lib.find(".so");
    std::size_t size = end_pos - st_pos;
    return lib.substr(st_pos, size);
}

bool Ncurse::isValid(char c)
{
    if (c >= 97 && c <= 122)
        return true;
    if (c >= 65 && c <= 90)
        return true;
    if (c >= '0' && c <= '9')
        return true;
    if (c == ' ' || c == '\t')
        return true;
    return false;
}

void Ncurse::getName(int c)
{
    if (st != menu_state::MENU_CHOICE || choice_option != 0)
        return;
    if (name.length() > 12)
        return;
    if (this->isValid(c))
        name += c;
    if (c == KEY_BACKSPACE && name.length() > 0) {
        name.erase(name.length() - 1, 1);
        wclear(input_area);
        wrefresh(input_area);
        box(input_area, 0, 0);
    }
}
