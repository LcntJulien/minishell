/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:06:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/15 17:22:21 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/include/libft.h"

typedef struct s_shell
{
	char			*input;
	char			*pwd;
	char			*oldpwd;
	char			**env;
	int				in;
	int				out;
	int				rtn;
	int				pid;
	int				exit;
}					t_shell;

typedef struct s_token
{
	char			*s;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

/*	SRC	*/

/*	BUILTIN	*/

/* echo */

/* env */
void	env(t_shell *mini, char **tab);

/*	PARSING	*/
void	parse(t_shell *mini);

/*	UTILS	*/
void	copy_env(t_shell *mini, char **env);
void	find_pwd(t_shell *mini);

#endif