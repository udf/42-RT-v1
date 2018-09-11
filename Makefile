# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 07:39:20 by mhoosen           #+#    #+#              #
#    Updated: 2018/09/10 21:23:17 by mhoosen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER_FILES=rt_v1.h util.h model.h view.h controller.h
SRC_FILES=main.c \
model.c model_util.c model_intersect.c model_normal_at.c model_scene.c \
model_scene_verify.c \
view.c view_render.c view_util.c \
controller.c
HEADERS=$(HEADER_FILES:%=includes/%)
SRCS=$(SRC_FILES:%=srcs/%)
NAME=RTv1
CFLAGS=-Wall -Wextra -Werror -g
INCLUDES=-I libft/includes -I lib3d/includes -I ./includes
LIBS=-L libft/ -L lib3d/ -lft -l3d -lm
SDL2_CONFIG=SDL2/bin/sdl2-config
SDL_SRCS=SDL2-2.0.8

all: $(NAME)

$(SDL_SRCS):
	curl -L https://www.libsdl.org/release/SDL2-2.0.8.tar.gz -o SDL2-2.0.8.tar.gz
	tar -xvzf $(SDL_SRCS).tar.gz

$(SDL2_CONFIG): $(SDL_SRCS)
	cd $(SDL_SRCS);\
	mkdir -p build;\
	cd build;\
	../configure --prefix=$(CURDIR)/SDL2;\
	make -j6; make install

$(NAME): $(SDL2_CONFIG) $(SRCS) $(HEADERS)
	make -C libft
	make -C lib3d
	gcc $(CFLAGS) $(SRCS) -o $(NAME) $(INCLUDES) $(LIBS) \
	 $(shell ./$(SDL2_CONFIG) --cflags --libs)

clean:
	@echo "No objects to clean"

fclean: clean
	rm -f $(NAME)

re: fclean all
