/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:11:51 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/04 15:03:10 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit_plus(t_shell *mini, t_token *token, int i)
{
	int	j;

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
	int	j;

	j = -1;
	if (i == 0)
	{
		ft_putstr_fd("Environnement cannot be loaded !\n", STDOUT_FILENO);
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
