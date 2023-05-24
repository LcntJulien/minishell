/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:06:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/24 16:15:10 by jmathieu         ###   ########.fr       */
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
	char			**env;
	char			**line;
}					t_shell;

typedef struct s_cmd
{
	
	int				fd_in;
	int				fd_out;
}					t_cmd;

/*	SRC	*/

/*	BUILTIN	*/

/* b_cd */

/* b_echo */
void	b_echo(t_shell *mini);

/* b_env */
void	b_env(t_shell *mini, char **tab);

/*	b_export	*/
void	b_export(t_shell *mini, char *str);

/*	b_pwd	*/
void	b_wd(t_shell *mini);

/*	b_unset	*/
void	b_unset(t_shell *mini);

/*	PARSING	*/
void	parse(t_shell *mini);

/*	UTILS	*/

/* utils */
void	copy_env(t_shell *mini, char **env);
char	*format_string(char *str);

/* ft_exit */
void	ft_exit(t_shell *mini, int i);

#endif