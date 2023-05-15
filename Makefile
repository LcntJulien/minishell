# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/29 13:00:26 by jlecorne          #+#    #+#              #
#    Updated: 2023/05/15 17:33:41 by jmathieu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PFXS	= srcs/

PFXB	= $(PFXS)builtin/

PFXT	= $(PFXS)utils/

SRCS	= $(PFXS)main.c			\
		$(PFXS)parsing/input.c	\
		$(PFXB)cd.c				\
		$(PFXB)echo.c			\
		$(PFXB)env.c			\
		$(PFXB)exit.c			\
		$(PFXB)export.c			\
		$(PFXB)pwd.c			\
		$(PFXB)unset.c			\
		$(PFXT)utils.c	
			
NAME	= minishell

CC		= gcc

LIBFT 	= libft/libft.a

HEADERS	= -I ./include -I "/Users/$$USER/.brew/opt/readline/include"
# HEADERS = -I libft/include -I ./include -I "/opt/homebrew/Cellar/readline/8.2.1/include"

LIBS = $(LIBFT) -lreadline -L"/Users/$$USER/.brew/opt/readline/lib"
# LIBS = $(LIBFT) -lreadline -L"/opt/homebrew/Cellar/readline/8.2.1/lib"

CFLAGS	= -Wall -Wextra -Werror

OBJS	= $(SRCS:.c=.o)

all		: $(NAME)

.c.o	:
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $(<:.c=.o)

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

debug 	: fclean $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) -fsanitize=address

lib		:
	@$(MAKE) -sC libft

clib	:
	@$(MAKE) clean -sC libft

fclib	:
	@$(MAKE) fclean -sC libft

rlib	:
	@$(MAKE) re -sC libft

.PHONY	: all, clean, fclean, re, debug, lib, clib, rlib