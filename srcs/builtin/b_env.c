/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:48:25 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/14 16:00:33 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_env(t_shell *mini)
{
	int		i;
	t_token	*list;

	list = mini->token;
	if (!list->next || (list->next && (list->next->type == 6
				|| list->next->type == 8 || list->next->type == 9)))
	{
		i = -1;
		while (mini->env[++i])
		{
			if (is_there_an_equal(mini->env[i]))
			{
				ft_putstr_fd(mini->env[i], STDOUT_FILENO);
				ft_putstr_fd("\n", STDOUT_FILENO);
			}
		}
		mini->rtn = 0;
	}
	else
		mini->rtn = 1;
}
