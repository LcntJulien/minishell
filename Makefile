# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/29 13:00:26 by jlecorne          #+#    #+#              #
#    Updated: 2023/09/18 18:10:25 by jlecorne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PFXS	= srcs/

PFXB	= $(PFXS)builtin/

PFXU	= $(PFXS)utils/

PFXP	= $(PFXS)parsing/

PFXE	= $(PFXS)exec/

SRCS	= $(PFXS)main.c			\
		$(PFXP)split/split.c	\
		$(PFXP)split/split_u.c	\
		$(PFXP)utils/utils.c	\
		$(PFXP)utils/utils1.c	\
		$(PFXP)var/var.c		\
		$(PFXP)var/var1.c		\
		$(PFXP)var/var2.c		\
		$(PFXP)input.c			\
		$(PFXP)error.c			\
		$(PFXP)token.c			\
		$(PFXP)type.c			\
		$(PFXE)redir/hrdc_u.c	\
		$(PFXE)redir/hrdc.c		\
		$(PFXE)redir/redir_u.c	\
		$(PFXE)redir/redir.c	\
		$(PFXE)utils/utils.c	\
		$(PFXE)utils/utils1.c	\
		$(PFXE)error.c			\
		$(PFXE)free.c			\
		$(PFXE)mem.c			\
		$(PFXE)minishell.c		\
		$(PFXB)b_process.c		\
		$(PFXB)b_utils.c		\
		$(PFXB)b_cd.c			\
		$(PFXB)b_cd_more.c		\
		$(PFXB)b_cd_exce.c		\
		$(PFXB)b_echo.c			\
		$(PFXB)b_echo_more.c	\
		$(PFXB)b_env.c			\
		$(PFXB)b_exit.c			\
		$(PFXB)b_exit_more.c	\
		$(PFXB)b_export.c		\
		$(PFXB)b_export_print.c	\
		$(PFXB)b_export_arg.c	\
		$(PFXB)b_var.c			\
		$(PFXB)b_pwd.c			\
		$(PFXB)b_unset.c		\
		$(PFXU)u_create_env.c	\
		$(PFXU)u_env_excepts.c	\
		$(PFXU)u_utils.c		\
		$(PFXU)u_exit.c			\
		$(PFXU)u_history.c		\
		$(PFXU)u_free.c			\
		$(PFXU)u_sig.c			\
		$(PFXU)u_sig_forked.c	\
		$(PFXU)u_sig_piped.c	\
		$(PFXU)u_sig_hdrc.c		

		
NAME	= minishell

CC		= gcc

LIBFT 	= -lft -L ./libft

# HEADERS = -I ./include -I "/Users/$$USER/.brew/opt/readline/include"
HEADERS = -I ./include -I "/opt/homebrew/Cellar/readline/8.2.1/include"

# LIBS = $(LIBFT) -lreadline -L"/Users/$$USER/.brew/opt/readline/lib"
LIBS = $(LIBFT) -lreadline -L "/opt/homebrew/Cellar/readline/8.2.1/lib"

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