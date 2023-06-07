/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:20 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/07 15:07:28 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_echo(t_shell *mini)
{
	t_token	*list;
	int		nb_args;

	nb_args = 0;
	if (!mini->token->next)
	{
		mini->rtn = 1;
		return ;
	}
	else
	{
		list = mini->token;
		while (list)
		{
			//OPTION A RAJOUTER
			if ((list->type >= 0 && list->type >= 2) || list->type == 4)
			{
				nb_args++; 
				list = list->next;
			}
			else
				break ;
		}
		list = mini->token;
		//if (nb_args != 0)
			//b_echo_args(mini, list, nb_args);
	}
	free(list);
	// a modifier free liste chainee
}
