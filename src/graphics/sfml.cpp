// /*
// ** EPITECH PROJECT, 2024
// ** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
// ** File description:
// ** sfml
// */
#include "sfml.hpp"
#include <SFML/Graphics.hpp>

extern "C" {
    std::string get_type()
    {
        return "graphic";
    }
    arcade::IGraphic *creater()
    {
        return new Sfml();
    }
}

Sfml::Sfml() {
    snake_body.setSize(sf::Vector2f(14, 14));
    tile.setSize(sf::Vector2f(14, 14));
    tile.setFillColor(sf::Color::Red);
    snake_body.setOutlineColor(sf::Color::White);
    snake_body.setFillColor(sf::Color::White);
    snake_fruit.setRadius(7);
    shape.setRadius(7);
    point.setRadius(2.5);
    shape.setFillColor(sf::Color::Yellow);
    snake_fruit.setOutlineColor(sf::Color::Red);
    snake_fruit.setFillColor(sf::Color::Red);
    window.create(sf::VideoMode(1900, 1100), "ARCADE GAME");
    idle_texture.loadFromFile("ressources/Idle.png");
    exit_texture.loadFromFile("ressources/quit.png");
    start_texture.loadFromFile("ressources/start.png");
    sprite_idle.setTexture(idle_texture);
    exit_sprite.setTexture(exit_texture);
    play_sprite.setTexture(start_texture);
    font.loadFromFile("ressources/Poppins-Black.ttf");
    back_text.loadFromFile("ressources/back.jpg");
    back.setTexture(back_text, true);
    play_sprite.setScale(sf::Vector2f(2,1));
    exit_sprite.setScale(sf::Vector2f(2,1));
    exit_sprite.setPosition(837, 290);
    play_sprite.setPosition(820, 229);
    gameIndex = -1;
    libIndex = -1;
    canStart = false;
    this->init_game_screen();
    this->init_name_input();
}

Sfml::~Sfml()
{
}

bool Sfml::isOpen() {
    if (window.isOpen()) {
        return true;
    } else {
        return false;
    }
}

void Sfml::close_win() {
    window.close();
}

arcade::Keyboard Sfml::menu_event(std::map<int, std::string> &graph, std::map<int, std::string> &game, sf::Event &event)
{
    if (event.type == event.MouseButtonPressed) {
        for (int i = 0; i < gameBox.size(); i++) {
            if (gameBox[i].isHover(window)) {
                gameIndex = i;
                break;
            }
        }
        for (int i = 0; i < libBox.size(); i++) {
            if (libBox[i].isHover(window)) {
                libIndex = i;
                break;
            }
        }
        if (this->isSpriteHover(play_sprite, window) && canStart && !input.getData().empty()) {
            graph[1] = gh[libIndex + 1]; game[1] = gm[gameIndex + 1];
            return arcade::Keyboard::KeyEnter;
        }
        if (this->isSpriteHover(exit_sprite, window)) {
            window.close(); return arcade::Keyboard::keyQuit;
        }
    }
    if (gameIndex >= 0 && !canStart)
        canStart = true;
    return arcade::Keyboard::keyNone;
}

arcade::Keyboard Sfml::getUserInput(std::map<int, std::string> &graphlist, std::map<int, std::string> &gamelist, arcade::graphic_state &state) 
{
    sf::Event event;
    graphlist.clear();
    gamelist.clear();
    arcade::Keyboard key;
    while (window.pollEvent(event)) {
        this->input_event(event);
        if (event.type == sf::Event::Closed) {
            close_win();
            return arcade::Keyboard::keyQuit;
        }
        key = this->menu_event(graphlist, gamelist, event);
        if (key != arcade::Keyboard::keyNone)
            return key;
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left) {
                return arcade::Keyboard::keyLeft;
            } else if (event.key.code == sf::Keyboard::Right) {
                return arcade::Keyboard::keyRight;
            } else if (event.key.code == sf::Keyboard::Up){
                return arcade::Keyboard::KeyUp;
            } else if (event.key.code == sf::Keyboard::Down) {
                return arcade::Keyboard::keyDown;
            } else if (event.key.code == sf::Keyboard::Space) {
                return arcade::Keyboard::keyQuit;
            } else if (event.key.code == sf::Keyboard::G && state == arcade::graphic_state::GAME_STATE) {
                state = arcade::graphic_state::MENU_STATE;
                return arcade::Keyboard::keyMenu;
            } else if (event.key.code == sf::Keyboard::S) {
                return arcade::Keyboard::KeySwitch;
            } else if (event.key.code == sf::Keyboard::N && state == arcade::graphic_state::GAME_STATE) {
                return arcade::Keyboard::KeySwitchGame;
            }
        }
    }
    return arcade::Keyboard::keyNone;
}

void Sfml::displayMap(std::vector<std::string> map) {
    int i = 0;
    sf::Vector2f snake_pos{50, 100}; sf::Vector2f fruit_pos{50, 100};
    for(i = 0; i < map.size(); i++) {
        for(int j = 0; j < map[i].length(); j++) {
            if (map[i].at(j) == '#') {
                tile.setPosition(snake_pos);
                window.draw(tile);
            }
            if (map[i].at(j) == 'O') {
                snake_body.setPosition(snake_pos);
                window.draw(snake_body);
            }
            if (map[i].at(j) == '*') {
                snake_fruit.setPosition(fruit_pos);
                window.draw(snake_fruit);
            }
            if (map[i].at(j) == 'C') {
                shape.setPosition(snake_pos);
                window.draw(shape);
            }
            if (map[i].at(j) == '.') {
                point.setPosition(sf::Vector2f(snake_pos.x + 4, snake_pos.y + 4));
                window.draw(point);
            }
            snake_pos.x += 14;
            fruit_pos.x += 14;
        }
        snake_pos.y += 14;
        fruit_pos.y += 14;
        snake_pos.x = 50;
        fruit_pos.x = 50;
    }
}

std::string Sfml::getLibName(std::string lib)
{
    std::string proto = "arcade_";
    std::size_t pos = lib.find(proto);
    std::size_t st_pos = pos + proto.length();
    std::size_t end_pos = lib.find(".so");
    std::size_t size = end_pos - st_pos;
    return lib.substr(st_pos, size);
}

void Sfml::launch_display(std::vector<std::string> map, arcade::graphic_state &state, std::map<int, std::string> &graphic_libs, std::map<int, std::string> &games_lib)
{
    window.clear();
    gh = graphic_libs;
    gm = games_lib;
    window.draw(back);
    if (state == arcade::graphic_state::MENU_STATE) {
        this->init_sfml_box(graphic_libs, games_lib);
        this->loadResources();
        window.draw(exit_sprite);
        if (canStart) {
            window.draw(play_sprite);
            input.display(window);
        }
        for (int i = 0; i < libBox.size(); i++) {
            if (libBox[i].isHover(window) || i == libIndex) {
                libBox[i].scale(sf::Vector2f(1.09, 1.01));
                libBox[i].setBackColorRGB(4, 51, 50);
            } else {
                libBox[i].scale(sf::Vector2f(1,1));
                libBox[i].setBackColorRGB(13, 90, 88);
            }
            libBox[i].display(window);
        }
        for (int i = 0; i < gameBox.size(); i++) {
            if (gameBox[i].isHover(window) || i == gameIndex) {
                gameBox[i].setBackColorRGB(4, 51, 50);
                gameBox[i].scale(sf::Vector2f(1.09, 1.01));
            } else {
                gameBox[i].setBackColorRGB(13, 90, 88);
                gameBox[i].scale(sf::Vector2f(1,1));
            }
            gameBox[i].display(window);
        }
        if (this->isSpriteHover(exit_sprite, window)) {
            exit_sprite.setScale(sf::Vector2f(2.09, 1.01));
        } else {
            exit_sprite.setScale(sf::Vector2f(2,1));
        }
        if (this->isSpriteHover(play_sprite, window) && canStart) {
            play_sprite.setScale(sf::Vector2f(2.09, 1.01));
        } else if (canStart){
            play_sprite.setScale(sf::Vector2f(2,1));
        }
    } else {
        game_screen.display(window);
        // score_screen.display(window);
        displayMap(map);
    }
    window.display();
}

void Sfml::setScore(int score)
{
    display_score = score;
    // if (!_name.empty())
    //     user = _name;
}

std::string Sfml::getUsername()
{
    return user;
}
