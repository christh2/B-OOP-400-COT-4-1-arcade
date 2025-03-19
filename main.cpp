/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** main.cpp
*/
#include "Arcade.hpp"

int main(int ac, char **av)
{
    arcade::Core core;
    // std::string entryPoint = av[1];
    core.initConsole(av[1], ac);
    core.launchConsole();
    return 0;
}
