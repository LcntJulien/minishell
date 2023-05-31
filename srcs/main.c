/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:07:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/31 12:50:45 by jmathieu         ###   ########.fr       */
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
	(void)env;
	mini->in = dup(STDIN_FILENO);
	mini->out = dup(STDOUT_FILENO);
	mini->rtn = 0;
	mini->exit = 0;
	copy_env(mini, env);
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
	t_shell	test;

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
		test = mini;
		while (test.token)
		{
			printf("arg = %s type = %d\n", test.token->s, test.token->type);
			test.token = test.token->next;
		}
		printf("\n");
	}
	listfree(mini.token);
	return (0);
}
