/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:06:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/06/08 19:38:28 by jmathieu         ###   ########.fr       */
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

/* b_process */
void				b_process(t_shell *mini);

/* b_utils */
int					tab_lines(char **tab);
int					is_there_an_equal(char *s);
int					max_len(int s1, int s2);
char				*define_word(char *str, int i, t_shell *mini);
int					is_variable(char *str, int i, t_shell *mini, int *len);

/* b_cd */
void				b_cd(t_shell*mini, t_token *list);

/* b_echo */
void				b_echo(t_shell *mini, t_token *list);

/* b_echo_utils */
int					print_variable(t_shell *mini, int i);
bool				without_quote_print(char *str, t_shell *mini);
bool				with_squote_print(char *str, t_shell *mini);
bool				with_dquote_print(char *str, t_shell *mini);

/* b_env */
char				**renew_env(t_shell *mini, int lines, t_token *tmp);
void				b_env(t_shell *mini);

/*	b_export	*/
int					check_existing_args(t_shell *mini, char *s);
void				b_export_args(t_shell *mini, t_token *list, int nb_args);
void				b_export(t_shell *mini, t_token *list);

/*	b_export_simple	*/
void				print_listed_env(t_shell *mini);

/*	b_export_arg	*/
char				**add_var_env(t_shell *mini, int lines, t_token *new);
void				sub_var_env(t_shell *mini, int lines, t_token *sub);

/*	b_pwd	*/
void				b_pwd(t_shell *mini);

/*	b_unset	*/
void				b_unset(t_shell *mini);

/*	b_free	*/
void				free_tab(char **tab);

/*	UTILS	*/

/* u_create_env */
void				copy_env(t_shell *mini, char **env);

/* u_utils */
int					check_nb_args(t_shell *mini, int i);
char				*var_name(t_shell *mini, char *str);
char				*var_content(t_shell *mini, char *str);

/* u_exit */
void				ft_exit_plus(t_shell *mini, t_token *token, int i);
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