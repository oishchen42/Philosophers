# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/05 13:13:52 by oishchen          #+#    #+#              #
#    Updated: 2025/09/05 16:16:16 by oishchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

FLAGS := -Wall -Wextra -Werror -I.
CC := cc

SRC_DIR := src
OBJ_DIR := obj

SRC_FILES := main.c libft_utils.c error_handler.c
OBJ_FILES := $(SRC_FILES:.c=.o)

SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ := $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@ -pthread

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)


$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@ -pthread

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re