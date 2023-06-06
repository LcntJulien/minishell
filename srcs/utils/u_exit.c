/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:11:51 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/06 08:44:56 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit_plus(t_shell *mini, t_token *token, int i)
{
	int j;

	j = -1;
	if (i == 0)
	{
		while (token->s)
		{
			free(token->s);
			token = token->next;
		}
		while (mini->env[++j])
			free(mini->env[j]);
		free(mini->env);
		exit(0);
	}
}

void	ft_exit(t_shell *mini, int i)
{
	int j;

	j = -1;
	if (i == 0)
	{
		printf("Environnement cannot be loaded !\n");
		exit(0);
	}
	if (i == 1)
	{
		while (mini->env[++j])
			free(mini->env[j]);
		free(mini->env);
		exit(0);
	}
}
