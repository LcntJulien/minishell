/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:44:07 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/17 14:36:00 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_echo(t_shell *mini)
{
	if (mini->token->next->s == "-n" && mini->token->next->next->s)
	{
		
		
	}
	else 
	{
		fork();
		
	}
}
