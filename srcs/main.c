/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:07:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/24 17:22:37 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	startshell(t_shell *mini, char **env)
{
	//mini->in = dup(STDIN_FILENO);
	//mini->out = dup(STDOUT_FILENO);
	//mini->rtn = 0;
	//mini->exit = 0;
	copy_env(mini, env);
	find_pwd(mini);
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
	while (1)
	{
		mini.input = readline("Minishell > ");
		divide_args(&mini);
	}
	free(mini.input);
	return (0);
}
