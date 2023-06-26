/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:49:24 by jlecorne          #+#    #+#             */
/*   Updated: 2023/06/26 20:45:50 by jlecorne         ###   ########.fr       */
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

void	close_pipes(int	**tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		close(tab[i][0]);
		close(tab[i][1]);
		i++;
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
