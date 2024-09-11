# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/23 11:29:41 by rchavez@stu       #+#    #+#              #
#    Updated: 2024/09/11 11:21:50 by rchavez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -I/usr/local/include -g -fsanitize=address

O_F = OBJ

MLXLIB = ./MLX42

# LFLAGS = -ldl -lglfw3 -pthread -lm -framework Cocoa -framework OpenGL -framework IOKit
LFLAGS = -ldl -lglfw -pthread -lm -framework Cocoa -framework OpenGL -framework IOKit

MLX = ./MLX42/build/libmlx42.a

LIBFT_F = MLibft

PLANE_F = 2DPlane

PLANE = $(PLANE_F)/plane.a

LIBFT = $(LIBFT_F)/libft.a

CFILES = main.c maps.c maps_fill.c player.c rays.c

OFILES = $(CFILES:%.c=$(O_F)/%.o)

all : $(NAME)

$(NAME) : $(MLX) $(LIBFT) $(OFILES) $(PLANE)
	$(CC) $(CFLAGS) -o $(NAME) $(LFLAGS) $(MLX) $(OFILES) $(LIBFT) $(PLANE)

$(O_F)/%.o : %.c | $(O_F)
	$(CC) $(CFLAGS) -o $@ -c $^

$(LIBFT) : $(LIBFT_F)
	@cd $(LIBFT_F) && make

$(PLANE) : $(PLANE_F)
	@cd $(PLANE_F) && make

$(PLANE_F) :
	@touch .gitmodules
	@git submodule add -f https://github.com/rodalcham/2DPlane.git

$(LIBFT_F) :
	@touch .gitmodules
	@git submodule add -f https://github.com/rodalcham/MLibft.git

$(MLX) : $(MLXLIB)
	@mkdir -p $(MLXLIB)/build
	@cd $(MLXLIB)/build && cmake .. && make -j4

$(O_F) : 
	@if [ ! -d $(O_F) ]; then\
		mkdir $(O_F);\
	fi

$(MLXLIB) :
	@touch .gitmodules
	@git submodule add -f https://github.com/codam-coding-college/MLX42.git

clean :
	@rm -fr $(O_F)

fclean : clean
	@rm -rf $(NAME) $(MLXLIB)

re : fclean all

.PHONY : all, clean, fclean, re