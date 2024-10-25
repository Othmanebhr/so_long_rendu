# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root <root@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/12 21:31:32 by root              #+#    #+#              #
#    Updated: 2024/10/25 13:42:37 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = so_long

# Compilateur et options
CC = cc
CFLAGS = -g -Wall -Wextra -Werror

# Fichiers source pour so_long
SRCS = so_long.c \
			so_long_utils.c \
			parse_map/parse_map.c \
			parse_map/walls.c \
			parse_map/collumns_and_line.c \
			parse_map/flood_file.c \
			game_alg/get_positions.c \
			game_alg/key_mv.c \
			game_alg/put_img.c \
			game_win_over/game.c \

# Dossier de libft
LIBFT_DIR = ./libft
LIBFT_SRC = $(LIBFT_DIR)/libft.a

# Dossier de miniLibX
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx.a

# Objets
OBJS = $(SRCS:.c=.o)

# Bibliothèques supplémentaires à lier
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

# Cibles
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_SRC) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(LIBFT_SRC):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

# Règle pour compiler les fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cible de nettoyage
clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re

