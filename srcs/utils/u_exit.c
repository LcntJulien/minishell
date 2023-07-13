/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:11:51 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/12 16:29:11 by jlecorne         ###   ########.fr       */
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
		exit(1);
	}
}

void	ft_exit(t_shell *mini, int i)
{
	int		j;

	j = -1;
	if (i == 0)
	{
		ft_putstr_fd("Environnement cannot be loaded !\n", 2);
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
