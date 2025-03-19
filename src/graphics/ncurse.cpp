/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** ncurse
*/
#include "ncurse.hpp"

extern "C" {
    arcade::IGraphic* creater()
    {
        // arcade::IGraphic *ins = new Ncurse();
        return new Ncurse;
    }
    std::string get_type()
    {
        return "graphic";
    }
}

Ncurse::Ncurse()
{
    open_state = false;
    window = nullptr;
    menu_str = new std::string[16];
    this->load_menu_str();
    st = MENU_GAMES;
    game_option = 0;
    lib_option = 0;
    choice_option = -1;
    name = "";
    this->loadResources();
}

Ncurse::~Ncurse()
{
    this->close_win();
    delete[] menu_str;
}

void Ncurse::load_menu_str()
{
    std::fstream file("ressources/3d_diagonal.txt");
    std::string buffer;
    int counter = 0;
    if (!file.is_open()) {
        std::exit(84);
    }
    while (std::getline(file, buffer)) {
        if (counter < 16) {
            menu_str[counter] = buffer;
        }
        counter++;
    }
    file.close();
}
// Menu methods
void Ncurse::init_menu()
{
    menu_mid = newwin(17, 85, 2, 50);
    menu_games = newwin(19, 47, 22, 12);
    menu_graphics = newwin(19, 47, 22, 125);
    menu_enter = newwin(10, 40, 24, 73);
    input_area = newwin(3, 20, 25, 83);
    wborder(menu_enter, '`', '`', '`', '`', '+', '+', '+', '+');
    wborder(menu_games, '`', '`', '`', '`', '+', '+', '+', '+');
    wborder(menu_graphics, '`', '`', '`', '`', '+', '+', '+', '+');
    box(menu_mid, 0, -1);
    box(menu_games, 0, 0);
    box(menu_graphics, 0, 0);
    box(menu_enter, 0, 0);
    box(input_area, 0, 0);
}

void Ncurse::display_menu(std::map<int, std::string> &graph, std::map<int, std::string> &game)
{
    int pair = 0;

    this->libFilter(graph, game);
    box(menu_mid, 0, -1);
    box(menu_games, 0, 0);
    box(menu_graphics, 0, 0);
    box(menu_enter, 0, 0);
    box(input_area, 0, 0);
    wborder(menu_enter, '`', '`', '`', '`', '+', '+', '+', '+');
    wborder(menu_graphics, '`', '`', '`', '`', '+', '+', '+', '+');
    wborder(menu_games, '`', '`', '`', '`', '+', '+', '+', '+');
    wborder(input_area, '|', '|', '-', '-', '+', '+', '+', '+');
    for (int i = 0; i < 16; i++) {
        mvwprintw(menu_mid, i + 1, 3, "%s", menu_str[i].c_str());
    }
    this->state_border();
    mvwprintw(menu_games, 2, 17, "VIDEO GAMES");
    mvwprintw(menu_graphics, 2, 17, "GRAPHICS LIBS");
    this->display_menu_state();
    this->display_menu_enter();
    wrefresh(menu_mid);
    wrefresh(menu_games);
    wrefresh(menu_graphics);
    wrefresh(menu_enter);
    wrefresh(input_area);
}

// 

void Ncurse::loadResources()
{
    open_state = true;
    initscr();
    start_color();
    if (!has_colors()) {
        std::cout << "No colors found\n";
        std::exit(84);
    }
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_RED);
    init_pair(4, COLOR_WHITE, COLOR_GREEN);
    noecho();
    window = newwin(40, 122, 0, 12);
    dash = newwin(10, 45, 0, 140);
    move(2, 12);
    box(window, 0, -1);
    box(dash, 0, -1);
    keypad(stdscr, true);
    curs_set(0);
    this->init_menu();
    refresh();
}

arcade::Keyboard Ncurse::getUserInput(std::map<int, std::string> &graphlist, std::map<int, std::string> &gamelist, arcade::graphic_state &state)
{
    graphlist.clear();
    gamelist.clear();
    int c = getch();
    timeout(60);
    arcade::Keyboard key;
    key = this->menu_event(c, graphlist, gamelist, state);
    if (key != arcade::Keyboard::keyNone)
        return key;
    if (c == ' ' && choice_option != 0)
        return arcade::Keyboard::keyQuit;
    if (c == KEY_RIGHT)
        return arcade::Keyboard::keyRight;
    if (c == KEY_LEFT)
        return arcade::Keyboard::keyLeft;
    if (c == KEY_UP)
        return arcade::Keyboard::KeyUp;
    if (c == KEY_DOWN)
        return arcade::Keyboard::keyDown;
    if ((c == 'g' || c == 'G') && choice_option != 0) {
        state == arcade::MENU_STATE ?
        state = arcade::GAME_STATE : state = arcade::MENU_STATE;
        return arcade::Keyboard::keyMenu;
    }
    if ((c == 's' || c == 'S') && choice_option != 0)
        return arcade::Keyboard::KeySwitch;
    if ((c == 'N' || c == 'n') && choice_option != 0 && state != arcade::graphic_state::MENU_STATE)
        return arcade::Keyboard::KeySwitchGame;
    return arcade::Keyboard::keyNone;
}

void Ncurse::displayMap(std::vector<std::string> map)
{
    box(window, 0, -1);
    box(dash, 0, -1);
    for (int i = 0; i < map.size(); i++) {
        wattron(window, COLOR_PAIR(1));
        mvwprintw(window, i + 1, 1, map[i].c_str());
        wattroff(window, COLOR_PAIR(1));
    }
    mvwprintw(dash, 2, 1, "%s: %d", name.c_str(), disp_score);
    noecho();
    wrefresh(window);
    wrefresh(dash);
}

void Ncurse::clear_console()
{
    clear();
    refresh();
}

void Ncurse::launch_display(std::vector<std::string> map, arcade::graphic_state &state,
    std::map<int, std::string>& graphic_libs, std::map<int, std::string> &games_lib)
{
    this->clear_console();
    if (state == arcade::graphic_state::MENU_STATE) {
        this->display_menu(graphic_libs, games_lib);
    } else {
        this->displayMap(map);
    }
}

void Ncurse::close_win()
{
    delwin(window);
    delwin(dash);
    delwin(menu_mid);
    delwin(menu_games);
    delwin(menu_graphics);
    delwin(menu_enter);
    delwin(input_area);
    endwin();
}

void Ncurse::setScore(int score)
{
    // if (!_name.empty())
    //     name = _name;
    disp_score = score;
}

std::string Ncurse::getUsername()
{
    return name;
}
