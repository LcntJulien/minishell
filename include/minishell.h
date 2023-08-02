/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:06:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/01 16:54:17 by jlecorne         ###   ########.fr       */
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

# define HRDC ".heredoc"

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

int					g_sig;

typedef struct s_token
{
	char			*s;
	int				idx;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_hrdc
{
	int				idx;
	char			**content;
	struct s_hrdc	*next;
}					t_hrdc;

typedef struct s_shell
{
	t_token			*token;
	t_hrdc			*hrdc;
	pid_t			*pid;
	pid_t			ppid;
	pid_t			cur_pid;
	char			**env;
	char			**paths;
	char			**args;
	char			*line;
	char			*cmd;
	char			*echo;
	char			*home;
	int				**tab;
	int				in;
	int				out;
	int				ncmd;
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
void				b_cd(t_shell *mini, t_token *list);

/* b_cd_more */
char				*folder2(t_shell *mini, t_token *list);
char				*folder1(t_shell *mini);
int					valid_path(t_shell *mini, char *tmp_path);

/* b_cd_exce */
void				modify_pwd_and_tmp(t_shell *mini, char *tmp);
void				modify_pwd(t_shell *mini, t_token *list);
void				modify_oldpwd(t_shell *mini, char *tmp_pwd, char **tmp);
void				check_var_status(t_shell *mini, t_token *list,
						char *tmp_path, char *cur_dir);

/* b_echo */
void				b_echo(t_shell *mini, t_token *list);

/* b_echo */
void				is_it_a_variable(t_shell *mini, t_token *tmp);
int					check_opt(t_token *list, int nb_opt);

/* b_env */
char				**renew_env(t_shell *mini, int lines, t_token *tmp);
void				b_env(t_shell *mini);

/* b_exit */
void				b_exit(t_shell *mini, t_token *list);

/* b_exit_more */
void				exit_until(t_shell *mini);
void				exit_too_much(t_shell *mini);

/*	b_export	*/
int					check_existing_args(t_shell *mini, char *s);
void				b_export_args(t_shell *mini, t_token *list, int nb_args);
void				b_export(t_shell *mini, t_token *list);

/*	b_export_print	*/
void				print_listed_env(t_shell *mini);

/*	b_export_arg	*/
char				**add_var_env(t_shell *mini, int lines, t_token *new);
void				sub_var_env(t_shell *mini, int lines, t_token *sub);

/* b_var.c */
void				sub_var_last_cmd(t_shell *mini);

/*	b_pwd	*/
void				b_pwd(t_shell *mini);

/*	b_unset	*/
void				b_unset(t_shell *mini, t_token *list);

/*
UTILS
*/

/* u_create_env */
int					get_shlvl(char *str);
void				alloc_env(t_shell *mini, char **env);

/* u_env_excepts */
int					check_last(t_shell *mini, char **env, int i);
int					check_shlvl(t_shell *mini, char **env, int i);
int					check_oldpwd(t_shell *mini, char **env, int i);

/* u_exit */
void				ft_exit_plus(t_shell *mini, char *err, int rtn);
void				ft_exit_all(t_shell *mini, int histo, int rtn);

/*	u_free	*/
void				free_str(char *tmp);
void				free_tab(char **tab);
void				free_env(t_shell *mini);

/* u_history */
int					create_history(int *histo);
void				add_histo(char *str, int histo);

/* u_signal*/
void				define_last(t_shell *mini);
void				define_signals(void);

/* u_signal_more*/
void				sigint_0_handler(void);
void				sigint_1_handler(void);
void				sigint_2_handler(void);

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
int					parse_err(t_shell *mini, t_token *tk, int err);
void				parse(t_shell *mini);

/* token.c */
void				*get_tokens(char *line);
void				token_idx(t_shell *mini);
void				display_tokens(t_token *token);

/* type.c */
int					is_sep(char *line, int i);
void				post_tk_type(t_token *tk, t_shell *mini);
void				tk_type(t_token *token);

/* utils.c */
void				space(char *line, int *i);
void				free_token(t_shell *mini, t_token *tk);
void				clean_tokens(t_token *tk);
int					syntax_check(t_shell *mini, int mode);
int					quote_state(char *line, int idx);
int					is_quote(t_token *tk);

/* utils1.c */
int					is_dollar(t_token *tk);
char				*clean_s(char *s);

/* var.c */
void				convert_var(t_shell *mini, t_token *tk);
int					contain_var(t_shell *mini, t_token *tk);
int					valid_var(t_shell *mini, char *s);

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
void				get_args(t_shell *mini, t_token *tk);
void				pipe_alloc(t_shell *mini);
void				get_paths(t_shell *mini);
char				*get_cmd(t_shell *mini);
char				**args_alloc(t_token *tk);
int					nb_cmd(t_shell *mini);

/* mem.c */
void				mini_free(t_shell *mini);
void				close_output(t_token *cp, t_token *cur);
void				close_pipes(t_shell *mini, int i, int sw);

/* free.c */
void				free_hrdc(t_shell *mini);
void				free_token(t_shell *mini, t_token *tk);
void				free_args(t_shell *mini);
void				free_pipe(t_shell *mini);
void				free_paths(t_shell *mini);

/* redir.c */
void				redir(t_shell *mini, t_token *tk, int i);
void				hrdc_manager(t_shell *mini);

/* redir2.c */
void				args_redir(t_shell *mini, t_token *tk);
void				redir_hrdc(t_shell *mini, t_token *cur);
int					is_redir(t_token *tk, int mode);

/* error.c */
void				err_manager(t_shell *mini, t_token *tk, int err);
void				clear_files(t_shell *mini, t_token *tk, char *s);
void				fds_err(t_shell *mini, char *fname);

#endif