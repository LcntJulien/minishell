/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:39:05 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/12 18:08:03 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	err_manager(t_shell *mini, t_token *tk, int err)
{
	ft_putstr_fd("minishell: ", 2);
	if (err == 0)
	{
		ft_putstr_fd(tk->s, 2);
		ft_putendl_fd(": command not found", 2);
		mini->rtn = 127;
		exit(127);
	}
	else if (err == 1)
		ft_putendl_fd("error creating pipe", 2);
	else if (err == 2)
		ft_putendl_fd("error forking process id", 2);
	else if (err == 3)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(tk->s, 2);
		ft_putendl_fd("'", 2);
		mini->rtn = 258;
		exit(258);
		//empecher de quiter le prog quand meet cette erreur
	}
	mini->rtn = EXIT_FAILURE;
	exit(EXIT_FAILURE);
}
