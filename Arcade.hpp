/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-hanniel.degbelo
** File description:
** Arcade.hpp
*/
//<>
#include <iostream>
#include <queue>
#include <dlfcn.h>
#include <map>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <memory>
#include <chrono>
#include <exception>
#ifndef ARCADE_HPP_
    #define ARCADE_HPP_
namespace arcade {
    enum ErrorType {
        NONE,
        DLERROR,
        ARG_ERROR,
        INVALID_FILE
    };
    class Error : public std::exception {
        public:
            Error(){};
            ~Error(){};
            const char *what() const throw();
            void setType(arcade::ErrorType t);
        private:
            ErrorType type;
    };
    enum Direction {
        RIGHT,
        LEFT,
        TOP,
        DOWN
    };
    enum graphic_state {
        MENU_STATE,
        GAME_STATE
    };
    enum Keyboard {
        keyNone,
        keyRight,
        keyLeft,
        keyDown,
        KeyUp,
        KeySwitch,
        KeySwitchGame,
        keyMenu,
        keyQuit,
        keyRestart,
        KeyEnter
    };
    class IGraphic {
    public:
        virtual ~IGraphic() = default;
        virtual arcade::Keyboard getUserInput(std::map<int, std::string> &graphlist, std::map<int, std::string> &gamelist, arcade::graphic_state &state) = 0; //Obtenir l'entrée du joueur
        virtual void launch_display(std::vector<std::string> map, arcade::graphic_state &state,
        std::map<int, std::string>& graphic_libs, std::map<int, std::string>& games_lib) = 0;
        virtual std::string getUsername() = 0;
        virtual void setScore(int score) = 0;
    };
    class IGame {
    public:
        virtual ~IGame() = default;
        virtual void setEvents(arcade::Keyboard key) = 0; // effectuer un evènement dans le jeu
        virtual void run() = 0; //Méthode de lancement d'une boucle de jeu
        virtual bool isOver() = 0; //Vérification de fin de jeu
        virtual void reset() = 0; //Initialisation des données de jeu
        virtual std::vector<std::string> getMap() = 0; // Obtention de la carte de jeu
        virtual int getScore() = 0; //obtenir le score du joueur
        virtual void setUsername(std::string name) = 0; // set le nom du joueur
    };
    template <typename T>
    class Loader {
    public:
        Loader(){
            data = nullptr;
        };
        ~Loader(){};
        T* getInstance(std::string lib) {
            data = dlopen(lib.c_str(), RTLD_NOW);
        
            if (!data) {
                std::cerr << dlerror() << std::endl;
                std::exit(84);
            }
            T* (*creater)(void) = (T*(*)(void))dlsym(data, "creater");
            if (!creater) {
                std::cout << "Fail to load symbole creater" << std::endl;
                dlclose(data);
                exit(84);
            }
            T *ins = creater();
            return ins;
        };

        void closeLib(void)
        {
            if (!data) {
                data = nullptr;
                std::cerr << "Load library needed" << std::endl;
                std::exit(84);
            }
            dlclose(data);
            data = nullptr;
        }

        std::string getType(std::string &lib) const
        {
            void *dat = nullptr;
            std::string (*get_type)(void);
            try {
                dat = dlopen(lib.c_str(), RTLD_LAZY);
                if (!dat) {
                    arcade::Error err;
                    err.setType(arcade::ErrorType::DLERROR);
                    throw err;

                }
            } catch(arcade::Error &e) {
                std::cerr << e.what() << std::endl;
                std::exit(84);
            }
            try {
                get_type = (std::string (*)(void))dlsym(dat, "get_type");
                arcade::Error err;
                err.setType(arcade::DLERROR);
                if (!get_type) {
                    throw err;
                }
                std::string str = get_type();
                dlclose(dat);
                return str;

            } catch (arcade::Error &e) {
                std::cerr << e.what() << std::endl;
                dlclose(dat);
                std::exit(84);
            }
            return "";
        }
    private:
        void *data;
    };

    class Core {
    public:
        Core();
        ~Core();
        std::string getGraphLib();
        void initConsole(const char *str, int ac);
        void launchConsole();
        std::string getLibName(std::string lib);
    private:
        std::unique_ptr<IGame> actual_game;
        std::unique_ptr<IGraphic> actual_lib;

        Loader<arcade::IGame> game_loader;
        Loader<arcade::IGraphic> graph_loader;

        std::map<int, std::string> graph_names;
        std::map<int, std::string> game_names;

        int graphLen;
        int gameLen;

        std::string entry;
        void *data;
        int graph_index;
        int game_index;
        arcade::graphic_state state;
        std::string user;
        int score;

        // private methods
        void load_library(std::string file, std::string ext); // Chargement des disquettes
        void load_graphic_lib();
        void key_event_management(arcade::Keyboard key,
        std::map<int, std::string>& graph, std::map<int, std::string>& game);
        void change_library(std::map<int, std::string> &graphlist, std::map<int, std::string> &gamelist);
        void change_game(int index);
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;
        void switch_lib();
        void switch_game();
    };
}

#endif
