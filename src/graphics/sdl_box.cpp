/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** sdl_box
*/
#include "sdl_box.hpp"

SdlBox::SdlBox()
{
    space = nullptr;
    texture = nullptr;
}

SdlBox::~SdlBox()
{
    if (space)
        SDL_FreeSurface(space);
    if (texture)
        SDL_DestroyTexture(texture);
}

void SdlBox::setVector(std::pair<int,int> pos)
{
    box.x = pos.first;
    box.y = pos.second;
    box.w = space->w + 4;
    box.h = space->h + 4;
}

void SdlBox::setValue(std::string str, TTF_Font *font, SDL_Color col, SDL_Renderer *rend)
{
    space = TTF_RenderText_Solid(font, str.c_str(), col);
    texture = SDL_CreateTextureFromSurface(rend, space);
}

void SdlBox::setBackColor(int r, int g, int b)
{
    color.r = r;
    color.g = g;
    color.b = b;
}

void SdlBox::display(SDL_Renderer *render)
{
    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(render, &box);
    SDL_RenderDrawRect(render, &box);
    SDL_Rect rect = {1, 1, space->w, space->h};
    SDL_Rect r = {box.x + 12, box.y + 12, box.w - 20, box.h - 20};
    SDL_RenderCopy(render, texture, &rect, &r);
}

bool SdlBox::isHover(int mouseX, int mouseY)
{
    SDL_Point mouse = {mouseX, mouseY};

    return SDL_PointInRect(&mouse, &box);
}

// Screen

SdlScreen::SdlScreen()
{

}

SdlScreen::~SdlScreen()
{

}

void SdlScreen::setScreen(std::pair<int,int> pos, std::pair<int,int> size, SDL_Color col)
{
    screen.x = pos.first;
    screen.y = pos.second;
    screen.w = size.first;
    screen.h = size.second;
    color = col;
}

void SdlScreen::display(SDL_Renderer *render)
{
    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(render, &screen);
    SDL_RenderDrawRect(render, &screen);
}
