/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** sfml
*/

#include "../../Arcade.hpp"
#include "sfml_box.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#ifndef SFML_HPP_
    #define SFML_HPP_

class Sfml: public arcade::IGraphic {
    public:
        Sfml();
        ~Sfml();
        bool isOpen(); //Vérification de la fenêtre
        arcade::Keyboard getUserInput(std::map<int, std::string> &graphlist, std::map<int, std::string> &gamelist, arcade::graphic_state &state); //Obtenir l'entrée du joueur
        void displayMap(std::vector<std::string> map); // Affichage de la map
        void launch_display(std::vector<std::string> map, arcade::graphic_state &state,
        std::map<int, std::string>& graphic_libs, std::map<int, std::string>& games_lib);
        std::string getLibName(std::string lib);
        void close_win();
        void setScore(int score);
        std::string getUsername();

    private:
        sf::RenderWindow window; 
        sf::RectangleShape rectangle_game; //box de liste de jeux
        sf::RectangleShape rectangle_lib; // box de liste de librairie graphiques
        sf::RectangleShape rec_menu; // Box de PLay ou Quit
        sf::RectangleShape snake_body;
        sf::RectangleShape tile;
        sf::CircleShape shape;
        sf::CircleShape point;
        sf::CircleShape snake_fruit;
        sf::Texture idle_texture;
        sf::Texture start_texture;
        sf::Texture exit_texture;
        sf::Sprite sprite_idle;
        sf::Sprite play_sprite;
        sf::Sprite exit_sprite;
        sf::Font font; // Police d'écriture
        int gameIndex; // Index de choix de jeu
        int libIndex; // Index de choix de lib
        bool isMouseClicked = false;
        std::vector<SfmlBox> gameBox;
        std::vector<SfmlBox> libBox;
        bool canStart;
        std::map<int, std::string> gm;
        std::map<int, std::string> gh;
        sf::Texture back_text;
        sf::Sprite back;
        SfmlBox game_screen;
        SfmlBox score_screen;
        SfmlInput input;
        int display_score;
        std::string user;

        void init_sfml_box(std::map<int, std::string> &graph, std::map<int, std::string> &game);
        void init_lib_box(SfmlBox &box, int index, char side);
        void loadResources();
        arcade::Keyboard menu_event(std::map<int, std::string> &graph, std::map<int, std::string> &game, sf::Event &event);
        bool isSpriteHover(sf::Sprite &sprite, sf::RenderWindow &window);
        void init_game_screen();
        void init_name_input();
        void input_event(sf::Event &event);
};
#endif
