/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:06:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/05 17:23:53 by jlecorne         ###   ########.fr       */
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

typedef struct s_shell
{
	t_token			*token;
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
	int				**htab;
	int				o_in;
	int				o_out;
	int				in;
	int				out;
	int				ncmd;
	int				rdr;
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

/* b_echo_more */
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
void				free2(char *one, char *two);

/* u_history */
int					create_history(int *histo);
void				add_histo(char *str, int histo);

/* u_signal*/
void				define_last(t_shell *mini);
void				define_signals(void);
void				define_signals_hrdc(void);

/* u_signal_more*/
void				sigint_0_handler(void);
void				sigint_1_handler(void);
void				sigint_hrdc(int sig);
void				sigquit_hrdc(int sig);

/* u_utils */
char				*var_content(t_shell *mini, char *str);
char				*return_var_content(t_shell *mini, char *var);
char				*var_name(t_shell *mini, char *str);
char				*return_var_name(t_shell *mini, char *var);
int					existing_var(t_shell *mini, char *var);

/* PARSING */

/* input.c */
void				parse_input(t_shell *mini);

/* utils */
void				display_tokens(t_token *token);
char				*clean_s(char *s);
int					quote_state(char *line, int idx);
int					str_alloc(char *s, int *idx);
int					is_sep(char *line, int i);
int					is_dollar(t_token *tk);
int					is_quote(char *s);

/* var */
void				convert_var(t_shell *mini, t_token *tk);
char				*get_vname(char *s, int idx);
int					contain_var(char *s);

/* var1 */
char				*rewrite(t_shell *mini, char *s, char *vname, int idx);
char				*get_nvar(t_shell *mini, char *vname);
char				*get_ns(char *s, char *nvar, int idx, int vname_len);

/* var2 */
char				*other_variable(t_shell *mini, t_token *tmp, int i);
char				*get_other_var(char *vname);
char				*rewrite2(char *s, char *iter, int idx);

/* token.c */
void				space(char *line, int *i);
void				token_idx(t_shell *mini);
void				clean_tokens(t_token *tk);
void				*get_token(char *line);

/* type.c */
void				post_tk_type(t_token *tk);
void				tk_type(t_token *token);

/* error.c */
int					parse_err(t_shell *mini, t_token *tk, int err);
int					syntax_check(t_shell *mini);

/*
UTILS
*/
/* cstm_split */
char				**custom_split(const char *s, char c, int sw);
char				**tabfree(char **p);
int					scount(const char *s, char c, int q);

/* EXEC */

/* minishell.c */
void				minishell(t_shell *mini);
t_token				*next_cmd(t_token *tk);

/* utils.c */
void				get_args(t_shell *mini, t_token *tk);
void				get_paths(t_shell *mini);
char				**args_alloc(t_token *tk);
char				*get_cmd(t_shell *mini);
int					nb_cmd(t_shell *mini);

/* mem.c */
void				close_pipes(t_shell *mini, int i, int sw);
void				close_output(t_token *cp, t_token *cur);
void				mini_free(t_shell *mini);
void				pipe_alloc(t_shell *mini);

/* free.c */
void				free_token(t_shell *mini);
void				free_paths(t_shell *mini);
void				free_htab(t_shell *mini);
void				free_args(t_shell *mini);
void				free_pipe(t_shell *mini);

/* hrdc.c */
int					solo_hrdc_filler(t_shell *mini, t_token *cur);
int					hrdc_manager(t_shell *mini);

/* hrdc1.c */
t_token				*cur_hrdc(t_token *tk);
void				alloc_htab(t_shell *mini, int nb);
int					get_htab(t_shell *mini, int i);
int					nb_hrdc(t_shell *mini);
int					is_hrdc(t_token *tk);

/* redir.c */
int					redir(t_shell *mini, t_token *tk, int i);

/* redir1.c */
int					solo_hrdc(t_shell *mini, t_token *cur);
void				args_redir(t_shell *mini, t_token *tk);
int					is_redir(t_token *tk, int mode);

/* error.c */
void				err_manager(t_shell *mini, t_token *tk, int err);
void				clear_files(t_shell *mini, t_token *tk, char *s);
void				fds_err(t_shell *mini, char *fname);

void				reset_std(t_shell *mini);

#endif