# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfatton <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/30 00:05:23 by lfatton           #+#    #+#              #
#    Updated: 2019/01/15 19:34:50 by lfatton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, run, norm, git, clean, fclean, re

NAME = wolf3d

SRC_PATH = srcs

SRC_NAME =	main.c \
			map_extractor.c \
			bmp_loader.c \
			map_verifs.c \
			environment.c \
			loop.c \
			raycasting.c \
			draw_utils.c \
			draw.c \
			motion.c \

SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ_PATH = objs

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

INCL_NAME = wolf3d.h

INCL_PATH = includes

SDL_NAME = SDL2-2.0.9

USER = $(shell whoami)

LIBFT_INCL_PATH = ./libft/includes

SDL_INCL_PATH = ./$(SDL_NAME)/include

INCL = $(addprefix $(INCL_PATH)/,$(INCL_NAME))

IFLAGS = -I $(INCL_PATH) -I $(LIBFT_INCL_PATH) -I $(SDL_INCL_PATH)

LDLIBFT = -L ./libft -lft

LIBS = -lm -lpthread

CC = clang

CFLAGS = -Wall -Werror -Wextra

ifeq ($(shell uname), Darwin)
	CONFIGURE_SDL = cd $(SDL_NAME) ; ./configure --prefix="/Users/$(USER)/$(SDL_NAME)"; $(MAKE) -j; $(MAKE) install
else
	CONFIGURE_SDL = cd $(SDL_NAME) ; ./configure ; $(MAKE) -j; sudo $(MAKE) install
endif

SDL_LDFLAGS = $(shell cd $(SDL_NAME) ; ./sdl2-config --libs)

SDL_CFLAGS = $(shell cd $(SDL_NAME) ; ./sdl2-config --cflags)

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@if [ ! -d "./$(SDL_NAME)/build" ] ; then $(CONFIGURE_SDL) ; fi
	@$(MAKE) -C libft
	@$(CC) $(OBJS) $(LDLIBFT) $(LIBS) $(SDL_LDFLAGS) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCL)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(IFLAGS) $(SDL_CFLAGS) -o $@ -c $<

run: $(NAME)
	@./$(NAME) assets/bmp/basic.bmp

norm:
	@norminette $(SRCS) $(INCL)

git: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean
	@git add -A
	@git status

clean:
	@$(RM) $(OBJS)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean
	@$(MAKE) -C $(SDL_NAME) clean

re: fclean all