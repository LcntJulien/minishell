# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/29 13:00:26 by jlecorne          #+#    #+#              #
#    Updated: 2023/06/12 14:20:48 by jmathieu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PFXS	= srcs/

PFXB	= $(PFXS)builtin/

PFXU	= $(PFXS)utils/

PFXP	= $(PFXS)parsing/

SRCS	= $(PFXS)main.c			\
		$(PFXP)input.c			\
		$(PFXP)utils.c			\
		$(PFXP)token.c			\
		$(PFXP)type.c			\
		$(PFXB)b_process.c		\
		$(PFXB)b_utils.c		\
		$(PFXB)b_cd.c			\
		$(PFXB)b_cd_more.c		\
		$(PFXB)b_cd_exce.c		\
		$(PFXB)b_echo.c			\
		$(PFXB)b_echo_utils.c	\
		$(PFXB)b_env.c			\
		$(PFXB)b_exit.c			\
		$(PFXB)b_export.c		\
		$(PFXB)b_export_simple.c\
		$(PFXB)b_export_arg.c	\
		$(PFXB)b_free.c			\
		$(PFXB)b_pwd.c			\
		$(PFXB)b_unset.c		\
		$(PFXU)u_create_env.c	\
		$(PFXU)u_utils.c		\
		$(PFXU)u_exit.c
NAME	= minishell

CC		= gcc

LIBFT 	= -lft -L ./libft

HEADERS	= -I ./include -I "/Users/$$USER/.brew/opt/readline/include"
# HEADERS = -I ./include -I "/opt/homebrew/Cellar/readline/8.2.1/include"

LIBS = $(LIBFT) -lreadline -L"/Users/$$USER/.brew/opt/readline/lib"
# LIBS = $(LIBFT) -lreadline -L "/opt/homebrew/Cellar/readline/8.2.1/lib"

CFLAGS	= -Wall -Wextra -Werror -ggdb3

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