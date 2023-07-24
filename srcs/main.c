/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:07:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/21 13:44:33 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	startshell(t_shell *mini, char **env, int *histo)
{
	mini->exit = 0;
	mini->pid = 0;
	mini->rtn = 0;
	mini->ncmd = 0;
	mini->cmd = NULL;
	mini->tab = NULL;
	mini->args = NULL;
	mini->paths = NULL;
	mini->line = NULL;
	mini->tab = NULL;
	mini->token = NULL;
	mini->hrdc = NULL;
	alloc_env(mini, env);
	//if (existing_var(mini, "HOME") != -1)
	mini->home = return_var_content(mini, "HOME");
	//else
		//mini->home = ft_strdup("/Users/jmathieu");
	if (!create_history(histo))
		ft_exit(mini, "Fail to create/iniate history\n", 1);
	rl_catch_signals = 0;
	mini->cur_pid = getpid();
	mini->ppid = getppid();
}

static void	args(int ac, char **av)
{
	(void)av;
	if (ac < 1 || ac > 1)
	{
		printf("Launch without any arguments\n");
		exit(1);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	mini;
	int		histo;

	args(ac, av);
	startshell(&mini, env, &histo);
	define_signals();
	while (1)
	{
		mini_free(&mini);
		mini.line = readline("\033[0;35m\033[1mminishell ▸ \033[0m");
		if (!mini.line)
			break ;
		if (mini.line[0])
		{
			add_histo(mini.line, histo);
			parse(&mini);
			// hrdc_manager(&mini);
			minishell(&mini);
		}
	}
	close(histo);
	ft_exit_all(&mini, 130);
}
