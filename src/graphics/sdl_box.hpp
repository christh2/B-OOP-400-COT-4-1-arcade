/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** sdl_box
*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
// #include <pair>
#ifndef SDL_BOX_HPP_
    #define SDL_BOX_HPP_

class SdlBox {
    public:
        SdlBox();
        ~SdlBox();
        void setVector(std::pair<int, int> pos);
        void setValue(std::string str, TTF_Font *font, SDL_Color col, SDL_Renderer *rend);
        void setBackColor(int r, int g, int b);
        void display(SDL_Renderer *render);
        bool isHover(int mouseX, int mouseY);
    private:
        SDL_Rect box;
        SDL_Surface *space;
        SDL_Texture *texture;
        SDL_Color color;
};

class SdlScreen {
    public:
        SdlScreen();
        ~SdlScreen();
        void setScreen(std::pair<int,int> pos, std::pair<int,int> size, SDL_Color col);
        void display(SDL_Renderer *render);
    private:
        SDL_Rect screen;
        SDL_Color color;
};

#endif /* !SDL_BOX_HPP_ */
