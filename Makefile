# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 17:05:06 by jalvarad          #+#    #+#              #
#    Updated: 2023/02/23 19:26:33 by jalvarad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = miniRT

# Source files #
SRC_FILES = main.c utils_attr_parser.c ft_mod_atof.c num_str_format.c\
			reader.c utils.c rgb.c generic_cleaners.c plane_parser.c\
			shapes_cleaners.c sphere_parser.c cylinder_parser.c\
			scene_cleaners.c scene_parser.c coords_parser.c\
			distance.c vector_operations.c vector_operations1.c screen.c \
			resolution.c shading.c open_window.c

OBJ_FILES = $(SRC_FILES:.c=.o)
# Directories #
SRC_DIR = srcs/
OBJ_DIR = obj/
HEADER_DIR = ./

# Todo junto #
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

# Libft #
LIBFT_DIR = ./Libft/

LIBFT = libft.a
#MLX42
LIBMLX_DIR = ./MLX42

# Includes #
HEADERS = -I ./ -I $(LIBMLX_DIR)/include
HEADER = miniRT.h
EXTRALIBS	:= $(LIBMLX_DIR)/build/libmlx42.a -ldl -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -pthread -lm
# Flags #
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
CC = gcc



all: install_cmake check_glfw make-libft libmlx $(NAME) 
	@echo "Proyect $(NAME) ready!"

libmlx:
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4

$(NAME): $(OBJ) $(HEADER_DIR)$(HEADER)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)$(LIBFT) $(EXTRALIBS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) $(HEADERS) -c $< -o $@

make-libft:
	@make -C $(LIBFT_DIR)

check_glfw:
	@brew ls --versions glfw || brew install glfw

ifeq (,$(shell which cmake))
install_cmake:
	brew install cmake
else
install_cmake:
	@echo "CMake already installed"
endif

bonus :
	make WITH_BONUS=1
clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ)
	@rm -f $(LIBMLX)/build

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)
re: fclean all

.PHONY: all re m clean fclean bonus