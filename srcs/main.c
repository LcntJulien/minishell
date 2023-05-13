/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:07:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/13 11:21:44 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	startshell(t_shell *mini)
{
	mini->in = dup(STDIN_FILENO);
	mini->out = dup(STDOUT_FILENO);
	mini->rtn = 0;
	mini->exit = 0;
}

static void	args(int argc, char **argv)
{
	(void)argv;
	if (argc < 1)
		exit (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	mini;
	char	*excmd;

	
	excmd = "exit";
	args(argc, argv);
	startshell(&mini);
	copy_env(&mini, envp);
	while (mini.exit == 0)
	{
		mini.input = readline("minishell $ ");
		if (ft_strncmp(excmd, mini.input, ft_strlen(mini.input)) == 0)
			mini.exit = 1;
		parse(&mini);
	}
	free(mini.input);
	return (0);
}
