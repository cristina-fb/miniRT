# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 17:05:06 by jalvarad          #+#    #+#              #
#    Updated: 2022/11/24 20:46:22 by jalvarad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = miniRT

# Source files #
SRC_FILES = main_jose.c parser.c ft_mod_atof.c num_str_format.c reader.c utils.c
#SRC_FILES = main.c distance.c vector_operations.c

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

# Includes #
HEADER = miniRT.h

# Flags #
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
CC = gcc

all: make-libft $(NAME) 
	@echo "Proyect $(NAME) ready!"

$(NAME): $(OBJ) $(HEADER_DIR)$(HEADER)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)$(LIBFT) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(HEADER_DIR)  -c $< -o $@

make-libft:
	@make -C $(LIBFT_DIR)

bonus :
	make WITH_BONUS=1
clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)
re: fclean all

.PHONY: all re m clean fclean bonus