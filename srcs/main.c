/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:07:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/13 14:47:40 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	startshell(t_shell *mini, char	**env, int *histo)
{
	mini->exit = 0;
	mini->pid = 0;
	mini->rtn = 0;
	mini->ncmd = 0;
	mini->cmd = NULL;
	mini->args = NULL;
	mini->paths = NULL;
	mini->line = NULL;
	mini->tab = NULL;
	alloc_env(mini, env);
	mini->home = return_var_content(mini, "HOME");
	if (!create_history(histo))
		ft_exit(mini, "Fail to create/iniate history\n", 1);
	define_signal = FALSE;
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

	rl_catch_signals = 0;
	args(ac, av);
	startshell(&mini, env, &histo);
	define_signals();
	while (!mini.exit)
	{
		mini_free(&mini);
		mini.line = readline("\033[0;35m\033[1mminishell ▸ \033[0m");
		if (!mini.line)
			break ;
		if (mini.line[0])
		{
			add_histo(mini.line, histo);
			parse(&mini);
			minishell(&mini);
			// mini_free(&mini);
		}
	}
	close(histo);
	ft_exit_all(&mini, 130);	
}
