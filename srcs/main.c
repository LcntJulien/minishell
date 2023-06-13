/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:07:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/06/13 15:02:53 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int sig)
{
	ft_putstr_fd("\033[0;35m\033[1mminishell ▸ \033[0m", 2);
	printf("Received SIGINT signal (%d)\n", sig);
	// system("leaks minishell");
	exit(0);
}

static void	startshell(t_shell *mini, char	**env)
{
	mini->in = dup(STDIN_FILENO);
	mini->out = dup(STDOUT_FILENO);
	mini->rtn = 0;
	mini->exit = 0;
	alloc_env(mini, env);
	mini->home = return_var_content(mini, "HOME");
}

static void	args(int ac, char **av)
{
	(void)av;
	if (ac < 1 || ac > 1)
	{
		printf("Launch without any arguments\n");
		exit(0);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	mini;

	args(ac, av);
	startshell(&mini, env);
	mini.rtn = 0;
	mini.exit = 0;
	signal(SIGINT, sigint_handler);
	while (mini.exit == 0)
	{
		mini.line = readline("\033[0;35m\033[1mminishell ▸ \033[0m");
		parse(&mini);
		b_process(&mini);
	}
	listfree(mini.token);
	return (0);
}
