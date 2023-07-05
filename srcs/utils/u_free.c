/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/05 19:11:35 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		free(tab);
	}
}

void	free_str(char **tmp)
{
	if (*tmp)
	{
		free(*tmp);
		*tmp = NULL;
	}
}

void	ft_free(t_shell *mini)
{
	int	i;

	i = -1;
	while (mini->env[++i])
		free(mini->env[i]);
	free(mini->env);
	listfree(mini->token);
}