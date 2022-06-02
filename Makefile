# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nboratko <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/12 20:31:07 by nboratko          #+#    #+#              #
#    Updated: 2022/05/31 16:11:45 by nboratko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = clang

CFLAGS =  -Wall -Wextra -Werror #-fsanitize=thread -g

SRCS = srcs/main.c \
       srcs/init.c \
       srcs/simulation.c \
       srcs/libft_utils.c \
       srcs/utils.c \
       srcs/utils2.c

_RED=	$'\033[1;31m
_GREEN=	$'\033[1;32m

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -lpthread -o $(NAME)
		@echo "$(_GREEN)Executable created : philo\33[0m"

%o: %.c
	$(CC) $(FLAGS) -I inc -O3 -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "$(_RED).o files removed\33[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "$(_RED)Executable removed\33[0m"

re: fclean all

.PHONY : all bonus clean fclean re
