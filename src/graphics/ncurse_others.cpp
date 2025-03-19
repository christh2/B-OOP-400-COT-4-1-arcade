/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** ncurse_others
*/
#include "ncurse.hpp"

void Ncurse::libFilter(std::map<int, std::string> &graph, std::map<int, std::string> &game)
{
    for (int i = 1; i < graph.size() + 1; i++) {
        gh[i] = std::make_pair(this->getLibName(graph[i]), graph[i]);
    }
    for (int i = 1; i < game.size() + 1; i++) {
        gm[i] = std::make_pair(this->getLibName(game[i]), game[i]);
    }
}
