/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** init_sdl_box
*/
#include "sdl.hpp"

std::string SDL::getLibName(std::string path)
{
    std::string proto = "arcade_";
    std::size_t pos = path.find(proto);
    std::size_t st_pos = pos + proto.length();
    std::size_t end_pos = path.find(".so");
    std::size_t size = end_pos - st_pos;
    return path.substr(st_pos, size);
}

void SDL::init_game_box(std::map<int, std::string> &game)
{
    std::pair<int,int> pos(200, 300);
    int bound = 0;
    SDL_Color color = {255,255,255};
    for (int i = 1; i < game.size() + 1; i++) {
        gameBox.push_back(SdlBox());
    }
    for (int i = 0; i < gameBox.size(); i++, bound += 90) {
        gameBox[i].setValue(this->getLibName(game[i + 1]), textFont, color, renderer);
        gameBox[i].setBackColor(13, 90, 88);
        gameBox[i].setVector(std::make_pair(pos.first, pos.second + bound));
    }
}

void SDL::init_graph_box(std::map<int, std::string> &graph)
{
    std::pair<int,int> pos(1700, 300);
    int bound = 0;
    SDL_Color color = {255,255,255};

    for (int i = 1; i < graph.size() + 1; i++) {
        libBox.push_back(SdlBox());
    }
    for (int i = 0; i < libBox.size(); i++, bound += 90) {
        libBox[i].setValue(this->getLibName(graph[i + 1]), textFont, color, renderer);
        libBox[i].setBackColor(13, 90, 88);
        libBox[i].setVector(std::make_pair(pos.first, pos.second + bound));
    }
}

void SDL::init_box(std::map<int, std::string> &graph, std::map<int, std::string> &game)
{
    std::pair<int,int> st_pos(900, 350);
    std::pair<int,int> quit_pos(900, 490);
    SDL_Color col = {255,255,255};
    this->init_game_box(game);
    this->init_graph_box(graph);
    start.setValue("START", textFont, col, renderer);
    start.setBackColor(25, 137, 47);
    start.setVector(st_pos);

    quit.setValue("QUIT", textFont, col, renderer);
    quit.setBackColor(255, 0, 0);
    quit.setVector(quit_pos);
}

void SDL::displayMenu()
{
    for (int i = 0; i < gameBox.size(); i++) {
        gameBox[i].display(renderer);
    }
    for (int i = 0; i < libBox.size(); i++) {
        libBox[i].display(renderer);
    }
    start.display(renderer);
    quit.display(renderer);
}

arcade::Keyboard SDL::menu_event_clic(std::map<int, std::string> &graph, std::map<int, std::string> &game, SDL_Event &event, arcade::graphic_state &state)
{
    if (event.type != SDL_MOUSEBUTTONDOWN)
        return arcade::Keyboard::keyNone;
    for (int i = 0; i < gameBox.size(); i++) {
        if (gameBox[i].isHover(event.button.x, event.button.y)) {
            gameIndex = i;
            break;
        }
    }
    for (int i = 0; i < libBox.size(); i++) {
        if (libBox[i].isHover(event.button.x, event.button.y)) {
            libIndex = i;
            break;
        }
    }
    if (start.isHover(event.button.x, event.button.y) &&
        gameIndex != -1 && libIndex != -1) {
        graph[1] = gh[libIndex + 1];
        game[1] = gm[gameIndex + 1];
        return arcade::Keyboard::KeyEnter;
    }
    if (quit.isHover(event.button.x, event.button.y)) {
        return arcade::Keyboard::keyQuit;
    }
    return arcade::Keyboard::keyNone;
}

void SDL::menu_mouse_motion(SDL_Event &event)
{
    if (event.type != SDL_MOUSEMOTION)
        return;
    for (int i = 0; i < gameBox.size(); i++) {
        if (gameBox[i].isHover(event.motion.x, event.motion.y) || gameIndex == i) {
            gameBox[i].setBackColor(4, 51, 50);
        } else {
            gameBox[i].setBackColor(13, 90, 88);
        }
    }
    for (int i = 0; i < libBox.size(); i++) {
        if (libBox[i].isHover(event.motion.x, event.motion.y) || libIndex == i) {
            libBox[i].setBackColor(4, 51, 50);
        } else {
            libBox[i].setBackColor(13, 90, 88);
        }
    }
}
