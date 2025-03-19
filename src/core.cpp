/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** core
*/
#include "../Arcade.hpp"

arcade::Core::Core()
{
    graphLen = 1;
    gameLen = 1;
    actual_game = nullptr;
    actual_lib = nullptr;
    graph_index = 1;
    game_index = -1;
    state = arcade::graphic_state::MENU_STATE;
    user = "";
    score = 0;
}

arcade::Core::~Core()
{
}

void arcade::Core::load_library(std::string file, std::string ext)
{
    std::string name;
    std::string type;

    if (ext != ".so")
        return;
    type = graph_loader.getType(file);
    if (type == "game") {
        game_names[gameLen] = file;
        gameLen++;
    }
    if (type == "graphic") {
        graph_names[graphLen] = file;
        graphLen++;
    }
}

void arcade::Core::load_graphic_lib()
{
    try {
        arcade::Error err;
        std::string type = graph_loader.getType(entry);
        if (type != "graphic") {
            err.setType(arcade::ErrorType::INVALID_FILE);
            throw err;
        }
    }
    catch (arcade::Error &e) {
        std::cerr << e.what() << std::endl;
        std::exit(84);
    }
    actual_lib.reset(graph_loader.getInstance(entry));

    for (int i = 1; i < graphLen; i++) {
        if (this->getLibName(entry) == this->getLibName(graph_names[i])) {
            graph_index = i;
            break;
        }
    }
}

std::string arcade::Core::getLibName(std::string lib)
{
    std::string proto = "arcade_";
    std::size_t pos = lib.find(proto);
    std::size_t st_pos = pos + proto.length();
    std::size_t end_pos = lib.find(".so");
    std::size_t size = end_pos - st_pos;
    return lib.substr(st_pos, size);
}

void arcade::Core::initConsole(const char *str, int ac)
{
    try {
        arcade::Error err;
        if (ac != 2) {
            err.setType(arcade::ARG_ERROR);
            throw err;
        }
    } catch (arcade::Error &e) {
        std::cerr << e.what() << std::endl;
        std::exit(84);
    }
    entry = str;
    std::srand(time(NULL));
    std::filesystem::path dir = "lib";
    std::string ext = "";
    std::string filepath = "";

    if (std::filesystem::exists(dir)) {
        for (auto file: std::filesystem::directory_iterator(dir)) {
            ext = file.path().extension();
            filepath = file.path();
            this->load_library("./" + filepath, ext);
        }
    }
    this->load_graphic_lib();
}

std::string arcade::Core::getGraphLib()
{
    return "";
}

void arcade::Core::change_game(int index)
{
    if (actual_game) {
        actual_game.reset(nullptr);
        game_loader.closeLib();
    }
    actual_game.reset(game_loader.getInstance(game_names[index]));
    game_index = index;
}

void arcade::Core::change_library(std::map<int, std::string> &graphlist, std::map<int, std::string> &gamelist)
{
    for (int i = 1; i < graphLen; i++) {
        if (this->getLibName(graphlist[1]) == this->getLibName(graph_names[i])
        && i != graph_index) {
            actual_lib.reset(nullptr);
            graph_loader.closeLib();
            graph_index = i;
            actual_lib.reset(graph_loader.getInstance(graph_names[i]));
            break;
        }
    }
    for (int i = 1; i < gameLen; i++) {
        if (this->getLibName(gamelist[1]) == this->getLibName(game_names[i])
        && i != game_index) {
            this->change_game(i);
            score = 0;
            break;
        }
        else if (this->getLibName(gamelist[1]) == this->getLibName(game_names[i])
            && i == game_index && actual_game && actual_game.get()->isOver()) {
            actual_game.get()->reset();
        }
    }
    actual_lib->setScore(score);
    user = actual_lib.get()->getUsername();
    actual_game.get()->setUsername(user);
}

void arcade::Core::key_event_management(arcade::Keyboard key, std::map<int,
    std::string>& graph, std::map<int, std::string>& game)
{
    if (key == arcade::Keyboard::KeySwitch) {
        this->switch_lib();
    }
    if (key == arcade::Keyboard::KeyEnter && state == arcade::graphic_state::MENU_STATE) {
        state = arcade::graphic_state::GAME_STATE;
        this->change_library(graph, game);
        return;
    }
    if (key == arcade::Keyboard::keyMenu) {
        state = arcade::graphic_state::MENU_STATE;
    }
    if (key == arcade::Keyboard::KeySwitchGame) {
        this->switch_game();
    }
}

void arcade::Core::switch_lib()
{
    if (graph_index + 1 < graphLen) {
        graph_index++;
        actual_lib.reset(nullptr);
        graph_loader.closeLib();
        actual_lib.reset(graph_loader.getInstance(graph_names[graph_index]));
    } else {
        graph_index = 1;
        actual_lib.reset(nullptr);
        graph_loader.closeLib();
        actual_lib.reset(graph_loader.getInstance(graph_names[graph_index]));
    }
    if (actual_game)
        score = actual_game.get()->getScore();
    actual_lib.get()->setScore(score);
}

void arcade::Core::switch_game()
{
    if (game_index + 1 < gameLen) {
        game_index++;
        actual_game.reset(nullptr);
        game_loader.closeLib();
        actual_game.reset(game_loader.getInstance(game_names[game_index]));
    } else {
        game_index = 1;
        actual_game.reset(nullptr);
        game_loader.closeLib();
        actual_game.reset(game_loader.getInstance(game_names[game_index]));
    }
    score = 0;
}
void arcade::Core::launchConsole()
{
    arcade::Keyboard key = arcade::Keyboard::keyNone;
    std::vector<std::string> map;
    std::map<int, std::string> graph_cpy;
    std::map<int, std::string> game_cpy;
    start = std::chrono::system_clock::now();
    while (key != arcade::Keyboard::keyQuit) {
        end = std::chrono::system_clock::now();
        graph_cpy = graph_names;
        game_cpy = game_names;
        if (actual_game != nullptr) {
            map = actual_game->getMap();
            score = actual_game->getScore();
        }
        actual_lib->setScore(score);
        actual_lib->launch_display(map, state, graph_cpy, game_cpy);
        key = actual_lib->getUserInput(graph_cpy, game_cpy, state);
        if (key == arcade::Keyboard::keyQuit) {
            actual_lib.reset(nullptr);
            graph_loader.closeLib();
            break;
        }
        this->key_event_management(key, graph_cpy, game_cpy);
        std::chrono::duration<double> sec = end - start;
        if (actual_game) {
            actual_game->setEvents(key);
        }
        if (actual_game && sec.count() > 0.07) {
            start = std::chrono::system_clock::now();
            actual_game->run();
        }
        if (actual_game && actual_game->isOver()) {
            state = arcade::graphic_state::MENU_STATE;
        }
    }
    if (actual_game) {
        actual_game.reset(nullptr);
        game_loader.closeLib();
    }
}

// exceptions
const char *arcade::Error::what() const throw()
{
    if (type == arcade::DLERROR) {
        return dlerror();
    }
    if (type == arcade::ARG_ERROR) {
        return "Invalid argument";
    }
    if (type == arcade::INVALID_FILE) {
        return "Invalid file";
    }
    return "";
}

void arcade::Error::setType(arcade::ErrorType t)
{
    type = t;
}
