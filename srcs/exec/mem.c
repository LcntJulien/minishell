/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:49:24 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/05 15:51:01 by jlecorne         ###   ########.fr       */
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

void	close_pipes(t_shell *mini, int tab[][2], int i, int sw)
{
	int j;

	j = 0;
	if (sw)
	{
		while (j < mini->ncmd)
		{
			if (j != i || i == 0)
				close(tab[j][0]);
			if (j != (i + 1))
				close(tab[j][1]);
			j++;
		}
	}
	else
	{
		while (j < mini->ncmd)
		{
			close(tab[j][0]);
			close(tab[j][1]);
			j++;
		}
	}
}

void	free_cpa(t_shell *mini)
{
	int	i;

	i = 0;
	while (mini->paths[i])
	{
		free(mini->paths[i]);
		i++;
	}
	free(mini->paths);
	i = 0;
	while (mini->args[i])
	{
		free(mini->args[i]);
		i++;
	}
	free(mini->args);
	free(mini->cmd);
}
