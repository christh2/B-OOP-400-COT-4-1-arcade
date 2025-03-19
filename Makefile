##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## make
##

CORE 	=	main.cpp \
			src/core.cpp

BIN 	=	arcade

SNAKE	=	src/games/snake.cpp \
			src/games/snake_move.cpp \
			src/games/grow_snake.cpp

PACMAN	=	src/games/pacman.cpp \
			src/games/pacman_moves.cpp

NIBBLER	=	src/games/nibbler.cpp

SFML	=	src/graphics/sfml.cpp \
			src/graphics/init_sfml_box.cpp \
			src/graphics/sfml_box.cpp

CURSE	=	src/graphics/ncurse.cpp \
			src/graphics/ncurse_event.cpp \
			src/graphics/ncurse_others.cpp

SDL		=	src/graphics/sdl.cpp \
			src/graphics/init_sdl_box.cpp \
			src/graphics/sdl_box.cpp

all:	graphicals games core

clean:
	rm -f *#
	rm -f *~
	rm -f lib/*.so
	rm -f vgcore*

fclean: clean
	rm -f $(BIN)

core: $(CORE)
	g++ $(CORE) -o $(BIN)

games:
	g++ $(SNAKE) -shared -o arcade_snake.so -fpic -ldl -fno-gnu-unique
	g++ $(PACMAN) -shared -o arcade_pacman.so -fpic -ldl -fno-gnu-unique
	mv *.so lib/

graphicals:
	g++ -shared -o arcade_ncurses.so $(CURSE) -lncurses -fpic -ldl -fno-gnu-unique
	g++ $(SFML) -shared -o arcade_sfml.so -lsfml-system -lsfml-graphics -lsfml-window -fpic -ldl -fno-gnu-unique
	g++ -shared -o arcade_sdl2.so $(SDL) -lSDL2 -lSDL2_ttf -lSDL2_image -fpic -ldl -fno-gnu-unique
	mv *.so lib/

re:	fclean all
