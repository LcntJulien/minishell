/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:49:24 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/14 18:29:25 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	mini_alloc(t_shell *mini, int ncmd)
// {
// 	mini->tab = malloc(sizeof(int *) * ncmd);
// 	if (!mini->tab)
// 		err_manager();
// 	mini->pid = malloc(sizeof(pid_t) * ncmd);
// 	if (!mini->pid)
// 		err_manager();
// }

void	close_pipes(t_shell *mini, int i, int sw)
{
	int	j;

	j = 0;
	if (sw)
	{
		while (j < mini->ncmd)
		{
			if (j != i || i == 0)
				close(mini->tab[j][0]);
			if (j != (i + 1))
				close(mini->tab[j][1]);
			j++;
		}
	}
	else
	{
		while (j < mini->ncmd)
		{
			close(mini->tab[j][0]);
			close(mini->tab[j][1]);
			j++;
		}
	}
}

void	mini_free(t_shell *mini)
{
	int	i;

	i = 0;
	if (mini->tab)
	{
		while (i < mini->ncmd)
			free(mini->tab[i++]);
		free(mini->tab);
	}
	free(mini->pid);
	i = 0;
	if (mini->tab)
	{
		while (mini->paths[i])
			free(mini->paths[i++]);
		free(mini->paths);
	}
	i = 0;
	if (mini->args)
	{
		while (mini->args[i])
			free(mini->args[i++]);
		free(mini->args);
	}
	if (mini->cmd)
		free(mini->cmd);
}
