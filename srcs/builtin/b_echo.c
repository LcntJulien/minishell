/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:20 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/17 17:16:21 by jmathieu         ###   ########.fr       */
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
