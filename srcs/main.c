/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:07:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/23 21:23:22 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int sig)
{
	ft_putstr_fd("\033[0;35m\033[1mminishell ▸ \033[0m", 2);
	printf("Received SIGINT signal (%d)\n", sig);
	system("leaks minishell");
	exit(0);
}

// static void	startshell(t_shell *mini)
// {
// 	mini->in = dup(STDIN_FILENO);
// 	mini->out = dup(STDOUT_FILENO);
// 	mini->rtn = 0;
// 	mini->exit = 0;
// }

static void	args(int argc, char **argv)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (argc < 1)
		exit (0);
	if (argc > 1)
	{
		while (argv[i])
		{
			if (argv[i][j] == ' ' || argv[i][j] == '\t')
				j++;
			else
				exit (0);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	mini;

	args(argc, argv);
	startshell(&mini);
	ft_env(&mini, envp);

	// mini.in = dup(STDIN_FILENO);
	// mini.out = dup(STDOUT_FILENO);
	mini.rtn = 0;
	mini.exit = 0;
	signal(SIGINT, sigint_handler);
	while (mini.exit == 0)
	{
		mini.line = readline("\033[0;35m\033[1mminishell ▸ \033[0m");
		parse(&mini);
	}
	listfree(mini.token);
	return (0);
}
