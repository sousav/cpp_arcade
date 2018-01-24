##
## Makefile for  in /home/sousa_v/rendu/cpp_arcade
##
## Made by Victor Sousa
## Login   <sousa_v@epitech.net>
##
## Started on  Mon Mar 13 22:42:09 2017 Victor Sousa
## Last update Sat Apr  8 22:17:41 2017 Sousa Victor
##

CPP		=	g++

NAME		=	arcade

RM		=	rm -f

MAKEFLAGS += --no-print-directory

LDFLAGS		+=	-ldl

CPPFLAGS	+=	-std=c++11
CPPFLAGS	+=	-Werror -Wall -Wextra -fpic -g
CPPFLAGS	+=	-I./includes/ -I./includes/utils -I./includes/utils/data

SRCSDIR		=	sources
UTILSDIR	=	$(SRCSDIR)/utils
DATASDIR	=	$(UTILSDIR)/data

SRCS		=	$(SRCSDIR)/main.cpp	\
			$(SRCSDIR)/Arcade.cpp	\
			$(SRCSDIR)/ScoreManager.cpp \
			$(SRCSDIR)/Menu.cpp

SRCS		+=	$(UTILSDIR)/Position.cpp	\
			$(UTILSDIR)/Color.cpp		\
			$(UTILSDIR)/Texture.cpp	\
			$(UTILSDIR)/DirectoryManager.cpp	\
			$(UTILSDIR)/Model3D.cpp

SRCS		+=	$(DATASDIR)/AData.cpp		\
			$(DATASDIR)/AVisual.cpp		\
			$(DATASDIR)/Audio.cpp		\
			$(DATASDIR)/Text.cpp		\
			$(DATASDIR)/AScene.cpp		\
			$(DATASDIR)/Camera.cpp		\
			$(DATASDIR)/Light.cpp		\
			$(DATASDIR)/Cube.cpp		\
			$(DATASDIR)/Sphere.cpp

OBJS		=	$(SRCS:.cpp=.o)

## LIB DIRECTORY
GAMEDIR		=	./games
SNAKEDIR	=	$(GAMEDIR)/Snake
SOLARDIR	=	$(GAMEDIR)/SolarFox

GRAPHDIR	=	./lib
NCURSESDIR	=	$(GRAPHDIR)/NCurses
SFMLDIR		=	$(GRAPHDIR)/SFML
OPENGLDIR	=	$(GRAPHDIR)/OpenGL

all:		games $(NAME)

dump:	all snake ncurses
dump_clean:	clean snake_clean ncurses_clean
dump_fclean:	fclean snake_fclean ncurses_fclean
dump_re:	re snake_re ncurses_re

global:	all games graph
global_clean:	clean games_clean graph_clean
global_fclean:	fclean games_fclean graph_fclean
global_re:	re games_re graph_re

games:		snake solar
games_clean:	snake_clean solar_clean
games_fclean:	snake_fclean solar_fclean
games_re:	snake_re solar_re

snake:
		@make -C $(SNAKEDIR)
snake_clean:
		@make -C $(SNAKEDIR) clean
snake_fclean:
		@make -C $(SNAKEDIR) fclean
snake_re:
		@make -C $(SNAKEDIR) re

solar:
		@make -C $(SOLARDIR)
solar_clean:
		@make -C $(SOLARDIR) clean
solar_fclean:
		@make -C $(SOLARDIR) fclean
solar_re:
		@make -C $(SOLARDIR) re

graph:		opengl sfml ncurses
graph_clean:	opengl_clean sfml_clean ncurses_clean
graph_fclean:	opengl_fclean sfml_fclean ncurses_fclean
graph_re:	opengl_re sfml_re ncurses_re

opengl:
		@make -C $(OPENGLDIR)
opengl_clean:
		@make -C $(OPENGLDIR) clean
opengl_fclean:
		@make -C $(OPENGLDIR) fclean
opengl_re:
		@make -C $(OPENGLDIR) re

sfml:
		@make -C $(SFMLDIR)
sfml_clean:
		@make -C $(SFMLDIR) clean
sfml_fclean:
		@make -C $(SFMLDIR) fclean
sfml_re:
		@make -C $(SFMLDIR) re

ncurses:
		@make -C $(NCURSESDIR)
ncurses_clean:
		@make -C $(NCURSESDIR) clean
ncurses_fclean:
		@make -C $(NCURSESDIR) fclean
ncurses_re:
		@make -C $(NCURSESDIR) re

$(NAME):		$(OBJS)
		@$(CPP) $(OBJS) $(LDFLAGS) -o $(NAME) && \
		printf "[\033[1;36mbuilt\033[0m] % 32s\n" $(NAME) | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $(NAME) | tr ' ' '.'

.cpp.o:
		@$(CPP) $(CPPFLAGS) $(LDFLAG) -c $< -o $@ && \
		printf "[\033[1;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $< | tr ' ' '.'

clean:		games_clean
		@$(RM) $(OBJS) && \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJ) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJ) | tr ' ' '.'

fclean:		games_fclean clean
		@$(RM) $(NAME) && \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.'

re:		fclean all
