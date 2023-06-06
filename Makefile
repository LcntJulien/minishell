# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/29 13:00:26 by jlecorne          #+#    #+#              #
#    Updated: 2023/06/06 18:00:09 by jlecorne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PFXS	= srcs/

PFXB	= builtin/

SRCS	= $(PFXS)main.c			\
		$(PFXS)parsing/input.c	\
		$(PFXS)parsing/utils.c	\
		$(PFXS)parsing/token.c	\
		$(PFXS)parsing/type.c
			
NAME	= minishell

CC		= gcc

LIBFT 	= -lft -L ./libft

# HEADERS	= -I ./include -I "/Users/$$USER/.brew/opt/readline/include"
HEADERS = -I ./include -I "/opt/homebrew/Cellar/readline/8.2.1/include"

# LIBS = $(LIBFT) -lreadline -L"/Users/$$USER/.brew/opt/readline/lib"
LIBS = $(LIBFT) -lreadline -L "/opt/homebrew/Cellar/readline/8.2.1/lib"

CFLAGS	= -Wall -Wextra -Werror

OBJS	= $(SRCS:.c=.o)

all		: $(NAME)

.c.o	: $(CC) $(CFLAGS) $(HEADERS) -c $< -o $(<:.c=.o)

$(NAME)	: lib $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "-- program created"

clean 	: clib
	@rm -f $(OBJS)
	@echo "-- all objects deleted"

fclean 	: fclib clean
	@rm -f $(NAME)
	@echo "-- program deleted"

re 		: fclean all

debug 	: fclean lib $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) -fsanitize=address

lib		:
	@$(MAKE) -sC libft

clib	:
	@$(MAKE) clean -sC libft

fclib	:
	@$(MAKE) fclean -sC libft

rlib	:
	@$(MAKE) re -sC libft

.PHONY	: all, clean, fclean, re, debug, lib, clib, fclib, rlib