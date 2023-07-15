/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:49:24 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/15 13:36:22 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_args(t_shell *mini)
{
	int	i;

	i = 0;
	if (mini->args)
	{
		while (mini->args[i])
			free(mini->args[i++]);
		free(mini->args);
		mini->args = NULL;
	}
}

void	free_pipe(t_shell *mini)
{
	int	i;

	i = 0;
	if (mini->tab)
	{
		while (i < mini->ncmd)
			free(mini->tab[i++]);
		free(mini->tab);
		mini->tab = NULL;
	}
}

void	free_paths(t_shell *mini)
{
	int	i;

	i = 0;
	if (mini->paths)
	{
		while (mini->paths[i])
			free(mini->paths[i++]);
		free(mini->paths);
		mini->paths = NULL;
	}
}

void	mini_free(t_shell *mini)
{
	free_pipe(mini);
	free_paths(mini);
	free_args(mini);
	if (mini->pid)
		free(mini->pid);
	mini->pid = NULL;
	if (mini->cmd)
		free(mini->cmd);
	mini->cmd = NULL;
	if (mini->line)
		free(mini->line);
	mini->line = NULL;
	listfree(mini->token);
}

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
