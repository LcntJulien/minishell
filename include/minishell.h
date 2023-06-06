/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:06:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/06/06 18:09:38 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef LIBFT
#  define LIBFT "../libft/include/libft.h"
# endif

# define CMD 0
# define ARG 1
# define VAR 2

# define OPTION 3
# define BUILTIN 4
# define DECLAVAR 5

# define PIPE 6
# define INPUT 7
# define OUTPUT 8
# define APPEND 9
# define HEREDOC 10

# include LIBFT
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_token
{
	char			*s;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_shell
{
	t_token			*token;
	char			**env;
	char			*line;
	int				in;
	int				out;
	int				rtn;
	int				pid;
	int				exit;
}					t_shell;

/*	BUILTIN	*/

/* b_cd */

/* b_echo */
void				b_echo(t_shell *mini);

/* b_env */
void				b_env(t_shell *mini, char **tab);

/*	b_export	*/
void				b_export(t_shell *mini, char *str);

/*	b_pwd	*/
void				b_wd(t_shell *mini);

/*	b_unset	*/
void				b_unset(t_shell *mini);
void				ft_env(t_shell *mini, char **envp);

/* utils */
void				copy_env(t_shell *mini, char **env);

/* ft_exit */
void				ft_exit(t_shell *mini, int i);

/* PARSING */

void				parse(t_shell *mini);
int					quote_state(char *line, int idx);
int					is_sep(char *line, int i);
void				*get_tokens(char *line);
void				space(char *line, int *i);
void				listfree(t_token *token);
void				post_tk_type(t_token *tk, t_shell *mini);
void				clean_tokens(t_token *tk);
void				tk_type(t_token *token);

#endif