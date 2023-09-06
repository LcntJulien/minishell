/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:07:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/05 18:32:18 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* left to do */
/*
 - si env avant autre fctn exec autre fctn ou display err
	-> (behavior changes if pipe or no)
 - leaks check / norminette check
*/

/* pour les builtins */
/*
 - cd must check if arg is an existing file/folder -> if file display file_err
	-> if neither display both_err
 - pwd exec whatever
 - export works only if alone or with correct identifiers
	-> some incorrects: `.`, `/`, `/:`
 - same as export for unset
 - exit needs digits to exit whithout err_msg but exit anyway
 - env always send err_msg if folled by anything but a redir or a valid cmd: ls,
	cat(+arg), ??? 
*/

void	reset_std(t_shell *mini)
{
	if (mini->rdr == 1 || mini->rdr == 3)
	{
		close(mini->in);
		dup2(STDIN_FILENO, mini->o_in);
		mini->rdr = 0;
	}
	if (mini->rdr == 2 || mini->rdr == 3)
	{
		close(mini->out);
		dup2(STDOUT_FILENO, mini->o_out);
		mini->rdr = 0;
	}
}

static void	startshell(t_shell *mini, char **env, int *histo,
		struct termios *term)
{
	mini->rtn = 0;
	mini->exit = 0;
	mini->pid = 0;
	mini->ncmd = 0;
	mini->rdr = 0;
	mini->o_in = dup(STDIN_FILENO);
	mini->o_out = dup(STDOUT_FILENO);
	mini->in = 0;
	mini->out = 0;
	mini->cmd = NULL;
	mini->tab = NULL;
	mini->args = NULL;
	mini->paths = NULL;
	mini->line = NULL;
	mini->tab = NULL;
	mini->htab = NULL;
	mini->token = NULL;
	alloc_env(mini, env);
	mini->home = ft_strdup(getenv("HOME"));
	if (!create_history(histo))
		ft_exit_plus(mini, "Fail to create/iniate history\n", 1);
	if (tcgetattr(STDIN_FILENO, term) == -1)
		ft_exit_plus(mini, "Fail to get terminal attributes\n", 1);
	rl_catch_signals = 0;
}

static void	args(int ac, char **av)
{
	(void)av;
	g_sig = 0;
	define_signals();
	if (ac > 1)
	{
		ft_putstr_fd("Launch without any arguments\n", STDERR_FILENO);
		exit(1);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell			mini;
	struct termios	term;
	int				histo;

	args(ac, av);
	startshell(&mini, env, &histo, &term);
	while (1)
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
			ft_exit_plus(&mini, "Fail to reload minishell attributes\n", 1);
		mini.line = readline("\033[0;35m\033[1mminishell ▸ \033[0m");
		if (!mini.line)
			break ;
		if (mini.line[0])
		{
			add_histo(mini.line, histo);
			parse_input(&mini);
			minishell(&mini);
		}
		mini_free(&mini);
	}
	ft_exit_all(&mini, histo, 130);
}
