/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** sdl
*/

#include "../../Arcade.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "sdl_box.hpp"

class SDL_Sprite {
    public:
        SDL_Sprite();
        ~SDL_Sprite();
        void load(std::string file, SDL_Renderer *rend);
        void draw(SDL_Renderer *rend);
    private:
        SDL_Texture *texture;
        SDL_Surface *space;

};

// void parcourir(std::queue<vector> queue)
// {
//     vector tmp;

//     for (int i = 0; i < queue.size(); i++) {
//         tmp = queue.front();
//         tmp.x = ?;
//         tmp.y = ?;
//         queue.pop();
//         queue.push(tmp);
//     }
// }

class SDL : public arcade::IGraphic {
public:
    SDL();
    ~SDL();

    void loadResources();
    bool isOpen();
    arcade::Keyboard getUserInput(std::map<int, std::string> &graphlist, std::map<int, std::string> &gamelist, arcade::graphic_state &state);
    void detecter_clic(arcade::graphic_state &state, int mouseX, int mouseY);
    void launch_display(std::vector<std::string> map, arcade::graphic_state &state, std::map<int, std::string>& graphic_libs, std::map<int, std::string>& games_lib);
    std::string getLibName(std::string lib);
    void close_win();
    std::string getUsername();
    void setScore(int score);

private:
    int menu;
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *textFont;
    SDL_Sprite back;
    std::vector<SdlBox> gameBox;
    std::vector<SdlBox> libBox;
    SdlBox start;
    SdlBox quit;
    int count;
    std::map<int, std::string> gh;
    std::map<int, std::string> gm;
    int gameIndex;
    int libIndex;
    SdlScreen game_screen;
    std::string name;
    int disp_score;
    

    // private methods
    void init_box(std::map<int, std::string> &graph, std::map<int,std::string> &game);
    void init_game_box(std::map<int, std::string> &game);
    void init_graph_box(std::map<int, std::string> &graph);
    void displayMenu();
    arcade::Keyboard menu_event_clic(std::map<int, std::string> &graph, std::map<int, std::string> &game, SDL_Event &event, arcade::graphic_state &state);
    void menu_mouse_motion(SDL_Event &event);
};
