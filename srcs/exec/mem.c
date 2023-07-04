/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:49:24 by jlecorne          #+#    #+#             */
/*   Updated: 2023/06/30 13:18:17 by jlecorne         ###   ########.fr       */
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

void	close_pipes(t_shell *mini, int tab[][2])
{
	int	i;

	i = 0;
	while (i < mini->ncmd)
	{
		close(tab[i][0]);
		close(tab[i][1]);
		i++;
	}
}

void	close_child(t_shell *mini, int tab[][2], int i)
{
	if (i == 0)
	{
		close(tab[i][0]);
		close(tab[i][1]);
		close(tab[i + 1][0]);
	}
	else if (i == mini->ncmd - 1)
	{
		close(tab[i - 1][0]);
		close(tab[i - 1][1]);
		close(tab[i][1]);
	}
	else
	{
		close(tab[i][1]);
		close(tab[i - 1][0]);
		close(tab[i - 1][1]);
		close(tab[i + 1][0]);
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
