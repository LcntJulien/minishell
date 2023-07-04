/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:06:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/04 11:57:46 by jlecorne         ###   ########.fr       */
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
	pid_t			*pid;
	char			**env;
	char			*line;
	char			*cmd;
	char			**args;
	char			**paths;
	int				ncmd;
	int				status;
	char			*home;
	int				in;
	int				out;
	int				rtn;
	int				exit;
}					t_shell;

/*
BUILTIN
*/

/* b_process */
void				b_process(t_shell *mini);

/* b_utils */
int					tab_lines(char **tab);
int					is_there_an_equal(char *s);
int					max_len(int s1, int s2);
int					check_nb_args(t_shell *mini, int i);

/* b_cd */
int					valid_path(t_shell *mini, char *tmp_path);
void				b_cd(t_shell*mini, t_token *list);

/* b_cd_exce */
void				modify_pwd_and_tmp(t_shell *mini, char *tmp);
void				modify_pwd(t_shell*mini, t_token *list);
void				modify_oldpwd(t_shell *mini, char *tmp_pwd, char **tmp);
void				check_var_status(t_shell *mini, t_token *list,
						char *tmp_path);

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

/*	b_export_print	*/
void				print_listed_env(t_shell *mini);

/*	b_export_arg	*/
char				**add_var_env(t_shell *mini, int lines, t_token *new);
void				sub_var_env(t_shell *mini, int lines, t_token *sub);

/*	b_pwd	*/
void				b_pwd(t_shell *mini);

/*	b_unset	*/
void				b_unset(t_shell *mini, t_token *list);

/*	b_free	*/
void				free_tab(char **tab);

/*	UTILS	*/

/* u_create_env */
void				alloc_env(t_shell *mini, char **env);

/* u_exit */
void				ft_exit_plus(t_shell *mini, t_token *token, int i);
void				ft_exit(t_shell *mini, int i);

/* u_history */
int					create_history(int *histo);
void				add_histo(char *str, int histo);

/* u_utils */
char				*var_content(t_shell *mini, char *str);
char				*return_var_content(t_shell *mini, char *var);
char				*var_name(t_shell *mini, char *str);
char				*return_var_name(t_shell *mini, char *var);
int					existing_var(t_shell *mini, char *var);

/*
PARSING
*/
/* input.c */
void				parse(t_shell *mini);

/* token.c */
void				*get_tokens(char *line);
void				display_tokens(t_token *token);

/* type.c */
int					is_sep(char *line, int i);
void				post_tk_type(t_token *tk, t_shell *mini);
void				tk_type(t_token *token);

/* utils.c */
int					quote_state(char *line, int idx);
void				space(char *line, int *i);
void				listfree(t_token *token);
void				clean_tokens(t_token *tk);
void				convert_var(t_token *tk, t_shell *mini);

/*
UTILS
*/

/* cstm_split */
char				**custom_split(const char *s, char c, int sw);
int					scount(const char *s, char c, int q);
char				**tabfree(char **p);

/*
EXEC
*/

/* minishell.c */
void				minishell(t_shell *mini);

/* utils.c */
void				get_paths(t_shell *mini);
char				**get_args(t_token *tk);
char				*get_cmd(t_shell *mini);
int					nb_cmd(t_shell *mini);

/* mem.c */
void				mini_alloc(t_shell *mini, int ncmd);
void				free_cpa(t_shell *mini);
void				close_pipes(t_shell *mini, int tab[][2]);
void				close_child(t_shell *mini, int tab[][2], int i);

/* redir.c */
int					is_redir(t_token *tk);

/* error.c */
void				err_manager(void);

#endif