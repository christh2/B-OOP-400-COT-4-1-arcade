#include "sdl.hpp"

int main() {
    SDL sdl;

    std::vector<std::string> map = {
        "############################",
        "#  o                       #",
        "#                          #",
        "#          *               #",
        "#                          #",
        "#                          #",
        "############################"
    };
    int mapSize = map.size();
    std::string tab[2] = {"arcade_sfml.so", "arcade_ncurses.so"};
    std::string arr[2] = {"arcade_snake.so", "arcade_pacman.so"};
    std::map<int, std::string> emptyMap;
    std::map<int, std::string> emptyMap2;
    for (int i = 0; i < 2; i++) {
        emptyMap[i + 1] = tab[i];
        emptyMap2[i + 1] = arr[i];
    }
    arcade::graphic_state state = arcade::graphic_state::MENU_STATE;
    while (sdl.isOpen()) {
        sdl.launch_display(map, state, emptyMap, emptyMap2);

        arcade::Keyboard input = sdl.getUserInput(emptyMap, emptyMap2, state);

        if (input == arcade::keyQuit) {
            // sdl.close_win();
            break;
        }
    }

    return 0;
}

