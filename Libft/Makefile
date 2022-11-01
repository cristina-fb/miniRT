# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 17:15:24 by jalvarad          #+#    #+#              #
#    Updated: 2022/11/01 10:50:35 by jalvarad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= libft.a

CC 			= gcc
CFLAGS 		= -Wall -Werror -Wextra

SRC_DIR 	= srcs/
SRC_NAMES 	=  ft_atoi.c \
				get_next_line.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_strchr.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_split.c \
				ft_strjoin.c \
				ft_strdup.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_strmapi.c \
				ft_isspace.c \
				ft_issign.c \
				ft_matrix_len.c \
				ft_free_matrix.c \
				ft_mod_lstnew.c \
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c

SRCS 		= $(addprefix $(SRC_DIR), $(SRC_NAMES))
OBJ_DIR 	= objs/
OBJ_NAMES 	= $(SRC_NAMES:.c=.o)
OBJS 		= $(addprefix $(OBJ_DIR), $(OBJ_NAMES))

HDR_NAMES 	= libft.h
HDR_DIR = ./
HDRS 		= $(addprefix $(HDR_DIR),$(HDR_NAMES))

HDR_INC 	= $(addprefix -I./, $(HDR_DIR))

RED			= \033[0;31m
GREEN 		= \033[0;32m
NONE 		= \033[0m

all: $(NAME) $(HDRS)

$(NAME): $(OBJ_DIR) $(OBJS) $(HDRS)
	@ar rc $@ $(OBJS)
	@ranlib $@
	@echo "\t[ $(GREEN)✔$(NONE) ] libft/libft.a library"

$(OBJ_DIR):
	@mkdir $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HDRS)
	@$(CC) $(CFLAGS) $(HDR_INC) -c $< -o $@

clean:
	@rm -Rf $(OBJ_DIR)
	@echo "\t[ $(RED)✗$(NONE) ] libft/$(OBJ_DIR) directory"

fclean: clean
	@rm -f $(NAME)
	@echo "\t[ $(RED)✗$(NONE) ] libft/$(NAME) library"

re: fclean all

.PHONY: all clean fclean re