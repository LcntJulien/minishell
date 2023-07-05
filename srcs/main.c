/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:07:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/05 16:38:56 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	// ft_putstr_fd("\033[0;35m\033[1mminishell ▸ \033[0m", 2);
	// printf("Received SIGINT signal (%d)\n", sig);
	// system("leaks minishell");
	exit(0);
}

static void	startshell(t_shell *mini, char	**env, int *histo)
{
	mini->rtn = 0;
	mini->exit = 0;
	mini->ncmd = 0;
	alloc_env(mini, env);
	mini->home = return_var_content(mini, "HOME");
	if (!create_history(histo))
		ft_exit_plus(mini, mini->token, 0);
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
	int		histo;

	args(ac, av);
	startshell(&mini, env, &histo);
	signal(SIGINT, sigint_handler);
	while (mini.exit == 0)
	{
		mini.line = readline("\033[0;35m\033[1mminishell ▸ \033[0m");
		// fprintf(stderr, "entrée standars: %s\n", mini.line);
		if (mini.line)
			add_histo(mini.line, histo);
		parse(&mini);
		// minishell(&mini);
	}
	listfree(mini.token);
	return (0);
}
