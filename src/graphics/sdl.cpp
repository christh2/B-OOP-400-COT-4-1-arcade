#include "sdl.hpp"
#include <iostream>

extern "C" {
    arcade::IGraphic* creater()
    {
        return new SDL();
    }
    std::string get_type()
    {
        return "graphic";
    }
}

SDL::SDL() : window(nullptr), renderer(nullptr) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        exit(84);
    }
    if (TTF_Init() != 0) {
        std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
        SDL_Quit();
        exit(84);
    }
    window = SDL_CreateWindow("Arcade SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1900, 1100, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        exit(84);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        exit(84);
    }
    textFont = TTF_OpenFont("ressources/Poppins-Black.ttf", 30);
    back.load("ressources/back.jpg", renderer);
    count = 0;
    gameIndex = -1;
    libIndex = -1;
    SDL_Color col = {9,104,83};
    game_screen.setScreen(std::make_pair(100,50), std::make_pair(1680, 534), col);
    name = "Anonymous";
    disp_score = 0;
}

SDL::~SDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(textFont);
    SDL_Quit();
}

void SDL::loadResources() {
}

bool SDL::isOpen() {
    return window != nullptr;
}

arcade::Keyboard SDL::getUserInput(std::map<int, std::string> &graphlist, std::map<int, std::string> &gamelist, arcade::graphic_state &state) {
    gamelist.clear();
    graphlist.clear();
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return arcade::keyQuit;
        }
        arcade::Keyboard key = this->menu_event_clic(graphlist, gamelist, event, state);
        if (key != arcade::Keyboard::keyNone)
            return key;
        this->menu_mouse_motion(event);
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    return arcade::KeyUp;
                case SDLK_DOWN:
                    return arcade::keyDown;
                case SDLK_LEFT:
                    return arcade::keyLeft;
                case SDLK_RIGHT:
                    return arcade::keyRight;
                case SDLK_s:
                    return arcade::KeySwitch;
                case SDLK_n:
                    return arcade::Keyboard::KeySwitchGame;
                default:
                    return arcade::keyNone;
            }
        }
    }
    return arcade::keyNone;
}


void SDL::detecter_clic(arcade::graphic_state &state, int mouseX, int mouseY) {
    int boutonW = 100;
    int boutonH = 30;

    int boutonX = 50;
    int boutonY = 90;


    boutonX = 317; //Start
    boutonY = 350;
    

    if (mouseX >= boutonX && mouseX <= boutonX + boutonW &&
        mouseY >= boutonY && mouseY <= boutonY + boutonH) {
        state = arcade::graphic_state::GAME_STATE;
    } else {
        state = arcade::graphic_state::MENU_STATE;
    }
    boutonX = 317;//QUIT
    boutonY = 450;

    if (mouseX >= boutonX && mouseX <= boutonX + boutonW &&
        mouseY >= boutonY && mouseY <= boutonY + boutonH) {
        close_win();
    }
}


void SDL::launch_display(std::vector<std::string> map, arcade::graphic_state &state, std::map<int, std::string>& graphic_libs, std::map<int, std::string>& games_lib) {
    gm = games_lib;
    gh = graphic_libs;
    if (count == 0) {
        this->init_box(graphic_libs, games_lib);
    }
    count++;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
        back.draw(renderer);

    if (state == arcade::graphic_state::MENU_STATE) {
        this->displayMenu();            
    } else {
        game_screen.display(renderer);
        int rectSize = 48;
        SDL_Rect rect = {48, 48, 14, 14};
        SDL_Rect point = {48, 48, 14, 14};
            // rect.y = 48;
        for (int i = 0; i < map.size(); i++, rect.y += 14) {
            rect.x = 48;
            point.x = 48;
            for (int j = 0; j < map[i].length(); j++, rect.x += 14, point.x += 14) {
                if (map[i].at(j) == '*') {
                    SDL_SetRenderDrawColor(renderer, 255, 2, 5, SDL_ALPHA_OPAQUE);
                } else if (map[i].at(j) == 'O') {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                } else if (map[i].at(j) == 'C') {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
                } else if (map[i].at(j) == '#') {
                    SDL_SetRenderDrawColor(renderer, 19, 63, 216, SDL_ALPHA_OPAQUE);
                } else if (map[i].at(j) == '.') {
                    SDL_SetRenderDrawColor(renderer,  255, 255, 255, SDL_ALPHA_OPAQUE);
                    SDL_RenderFillRect(renderer, &point);
                    SDL_RenderDrawRect(renderer, &point);
                }
                else {
                    continue;
                }
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void SDL::close_win() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
}

void SDL::setScore(int score)
{
    // if (!_name.empty())
    //     name = _name;
    disp_score = score;
}

std::string SDL::getUsername()
{
    return name;
}


// sdl sprite

SDL_Sprite::SDL_Sprite()
{

}

SDL_Sprite::~SDL_Sprite()
{
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(space);
}

void SDL_Sprite::load(std::string file, SDL_Renderer *rend)
{
    space = IMG_Load(file.c_str());
    texture = SDL_CreateTextureFromSurface(rend, space);
}

void SDL_Sprite::draw(SDL_Renderer *rend)
{
    SDL_RenderCopy(rend, texture, nullptr, nullptr);
}
