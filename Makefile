# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmathieu <jmathieu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/29 13:00:26 by jlecorne          #+#    #+#              #
#    Updated: 2023/05/10 12:36:04 by jmathieu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PFXS	= srcs/

PFXB	= builtin/

SRCS	= $(PFXS)main.c
			
NAME	= minishell

CC		= gcc

LIBFT 	= ./libft/libft.a

HEADERS	= ./include/ $(LIBFT) -I /bin/

FLAGS	= -Wall -Wextra -Werror

OBJS	= $(SRCS:.c=.o)

all		: $(NAME)

$(NAME)	: $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) -I $(HEADERS) -lreadline -o $(NAME)
	@echo "-- program created"

clean 	:
	@rm -f $(OBJS)
	@echo "-- all objects deleted"

fclean 	: clean
	@rm -f $(NAME)
	@echo "-- program deleted"

re 		: fclean all

debug 	: fclean $(OBJS) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJS) -I $(HEADERS) -o $(NAME) -fsanitize=address

lib		:
	@make -sC ./libft

clib	:
	@make fclean -sC ./libft

rlib	:
	@make re -sC ./libft

.PHONY	: all, clean, fclean, re, debug, lib, clib, rlib