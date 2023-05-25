/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:07:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/25 12:22:50 by jlecorne         ###   ########.fr       */
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

// static void	startshell(t_shell *mini)
// {
// 	mini->in = dup(STDIN_FILENO);
// 	mini->out = dup(STDOUT_FILENO);
// 	mini->rtn = 0;
// 	mini->exit = 0;
// copy_env(mini, env);
	// find_pwd(mini);
// }

static void	args(int argc, char **argv)
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
