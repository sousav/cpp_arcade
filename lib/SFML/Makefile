##
## Makefile for  in /home/sousa_v/rendu/cpp_arcade
##
## Made by Victor Sousa
## Login   <sousa_v@epitech.net>
##
## Started on  Mon Mar 13 22:42:09 2017 Victor Sousa
## Last update Thu Apr  6 02:13:02 2017 Sousa Victor
##

CPP		=	g++

NAME		=	lib_arcade_sfml.so

RM		=	rm -f

CPPFLAGS	+=	-std=c++11
CPPFLAGS	+=	-Werror -Wall -Wextra -fPIC
CPPFLAGS	+=	-I./includes/ -I../../includes/ -I../../includes/utils -I../../includes/utils/data -I/usr/local/include/

LDFLAGS		+=	-shared -L/usr/local/lib/ -L/usr/lib/ -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

SRCSDIR		=	sources
ROOTDIR		=	../../sources
UTILSDIR	=	$(ROOTDIR)/utils
DATASDIR	=	$(UTILSDIR)/data

SRCS		=	$(SRCSDIR)/SFMLWrapper.cpp

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

all:		$(NAME)

$(NAME):	$(OBJS)
		@$(CPP) $(OBJS) $(LDFLAGS) -o $(NAME) && \
		printf "[\033[1;36mbuilt\033[0m] % 32s\n" $(NAME) | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $(NAME) | tr ' ' '.'
		@cp -f $(NAME) ../$(NAME)

.cpp.o:
		@$(CPP) $(CPPFLAGS) -c $< -o $@ && \
		printf "[\033[1;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $< | tr ' ' '.'

clean:
		@$(RM) $(OBJS) && \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJ) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJ) | tr ' ' '.'

fclean:		clean
		@$(RM) ../$(NAME) && $(RM) $(NAME) && \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.'

re:		fclean all
