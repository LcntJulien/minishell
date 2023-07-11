/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:11:51 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/11 15:43:49 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit_var(t_shell *mini)
{
	int	i;

	i = -1;
	listfree(mini->token);
	while (mini->env[++i])
		free(mini->env[i]);
	free(mini->env);
	free_str(mini->home);
	free_tab(mini->args);
	free_tab(mini->paths);
	
}

void	ft_exit_plus(t_shell *mini)
{
	int	i;

	i = -1;
	listfree(mini->token);
	while (mini->env[++i])
		free(mini->env[i]);
	free(mini->env);
	free_str(mini->home);
	free_tab(mini->args);
	free_tab(mini->paths);
}

void	ft_exit(t_shell *mini, int i)
{
	int		j;

	j = -1;
	if (i == 0)
	{
		ft_putstr_fd("Environnement cannot be loaded !\n", STDOUT_FILENO);
		exit(1);
	}
	if (i == 1 || i == 2 || i == 3)
	{
		while (mini->env[++j])
			free(mini->env[j]);
		free(mini->env);
		if (i == 2 || i == 3)
		{
			perror("Trouble initiating the parsing of the line !");
			if (i == 3)
				listfree(mini->token);
		}
		exit(1);
	}
}
