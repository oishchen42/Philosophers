# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/05 13:13:52 by oishchen          #+#    #+#              #
#    Updated: 2025/09/13 14:37:12 by oishchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

FLAGS := -Wall -Wextra -Werror -I.
CC := cc

SRC_FILES := main.c libft_utils.c error_handler.c \
			start_threads.c routines.c cleanups.c \
			init_data.c routine_utils.c
OBJ_FILES := $(SRC_FILES:.c=.o)


all: $(NAME)

$(NAME) : $(OBJ_FILES)
	$(CC) $(FLAGS) $(OBJ_FILES) -o $@ -pthread

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@ -pthread

clean:
	rm -rf $(OBJ_FILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re