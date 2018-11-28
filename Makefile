# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfatton <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/30 00:05:23 by lfatton           #+#    #+#              #
#    Updated: 2018/11/28 20:35:17 by lfatton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, norm, git, clean, fclean, re

NAME = wolf3d

SRC_PATH = srcs

SRC_NAME =	main.c \
			parse.c \
			environment.c \
			image.c \

SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ_PATH = objs

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

INCL_NAME = wolf3d.h

INCL_PATH = includes

SDL_NAME = SDL2-2.0.9

LIBFT_INCL_PATH = ./libft/includes

SDL_INCL_PATH = ./$(SDL_NAME)/include

INCL = $(addprefix $(INCL_PATH)/,$(INCL_NAME))

IFLAGS = -I $(INCL_PATH) -I $(LIBFT_INCL_PATH) -I $(SDL_INCL_PATH)

LDLIBFT = -L ./libft -lft

LIBS = -lm -lpthread -lSDL2

CC = clang

CFLAGS = -Wall -Werror -Wextra -g

ifeq ($(shell uname), Darwin)
	CONFIGURE_SDL = cd $(SDL_NAME) ; ./configure --prefix="/Users/lfatton/42"; $(MAKE) ; $(MAKE) install
else
	CONFIGURE_SDL = cd $(SDL_NAME) ; ./configure ; $(MAKE) ; sudo $(MAKE) install
endif

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@if [ ! -d "./$(SDL_NAME)/build" ] ; then $(CONFIGURE_SDL) ; fi
	@$(MAKE) -C libft
	@$(CC) $(OBJS) $(LDLIBFT) $(LIBS) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCL)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<

run: $(NAME)
	./$(NAME) $(NAME)

norm:
	norminette $(SRCS) $(INCL)

git: fclean
	git add -A
	git status

clean:
	@$(RM) $(OBJS)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean
	@$(MAKE) -C $(SDL_NAME) clean

re: fclean all
