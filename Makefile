# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 17:05:06 by jalvarad          #+#    #+#              #
#    Updated: 2023/05/08 13:44:26 by jalvarad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

# Source files #
CLEANER_FILES = generic_cleaners.c\
				scene_cleaners.c\
				shapes_cleaners.c


PARSER_FILES = coords_parser.c\
				cylinder_parser.c\
				plane_parser.c\
				scene_parser.c\
				sphere_parser.c\
				torus_parser.c\
				utils_attr_parser.c

RENDER_FILES = distance.c\
				main.c\
				open_window.c\
				rgb.c\
				screen.c\
				shading.c\
				sdf.c\
				vector_operations.c\
				vector_operations1.c

UTILS_FILES = ft_mod_atof.c\
				num_str_format.c\
				reader.c\
				utils.c\
				functions_chargers.c\

CLEANER_DIR = cleaners/
PARSER_DIR = parser/
RENDER_DIR = render_motor/
UTILS_DIR = utils/

CLEANER_SRC = $(addprefix $(CLEANER_DIR), $(CLEANER_FILES))
PARSER_SRC = $(addprefix $(PARSER_DIR), $(PARSER_FILES))
RENDER_SRC = $(addprefix $(RENDER_DIR), $(RENDER_FILES))
UTILS_SRC = $(addprefix $(UTILS_DIR), $(UTILS_FILES))

SRC_FILES = $(CLEANER_SRC) $(PARSER_SRC) $(RENDER_SRC) $(UTILS_SRC)
			
OBJ_FILES = $(notdir $(SRC_FILES:.c=.o))

# Directories #
SRC_DIR = src/
OBJ_DIR = obj/
HEADER_DIR = include/

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

# Libft #
LIBFT_DIR = ./Libft/

LIBFT = libft.a
#MLX42
LIBMLX_DIR = ./MLX42

# Includes #
HEADERS = -I $(HEADER_DIR) -I $(LIBMLX_DIR)/include
HEADER_FILES = miniRT.h\
				minirt_errors.h\
				minirt_structs.h
HEADERS_PATHS = $(addprefix $(HEADER_DIR), $(HEADER_FILES))
#/opt/homebrew/Cellar/glfw/3.3.8/lib/  -> path for home
EXTRALIBS	:= $(LIBMLX_DIR)/build/libmlx42.a -ldl\
				-lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -pthread -lm

# Flags #
CFLAGS = -Wall -Wextra -Werror -fno-stack-protector -fomit-frame-pointer -Ofast
CC = gcc

all: obj install_cmake check_glfw make-libft libmlx $(NAME) 
	@echo "Proyect $(NAME) ready!"

libmlx:
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)$(LIBFT) $(EXTRALIBS) -o $(NAME)

# OBJECTS CREATION
$(OBJ_DIR)%.o: $(SRC_DIR)$(CLEANER_DIR)%.c $(HEADERS_PATHS)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) $(HEADERS) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)$(PARSER_DIR)%.c $(HEADERS_PATHS)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) $(HEADERS) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)$(RENDER_DIR)%.c $(HEADERS_PATHS)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) $(HEADERS) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)$(UTILS_DIR)%.c $(HEADERS_PATHS)
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

obj:
	@mkdir -p $(OBJ_DIR)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ)
	@rm -f $(LIBMLX)/build

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)
re: fclean all

bonus: all

.PHONY: all re m clean fclean bonus
