/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:11:25 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/28 13:16:07 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parse_err(t_shell *mini, t_token *tk, int err)
{
	ft_putstr_fd("minishell: ", 2);
	if (!err)
	{
		ft_putstr_fd(tk->s, 2);
		ft_putendl_fd(": syntax error", 2);
		mini->rtn = 127;
	}
	else
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(tk->s, 2);
		ft_putendl_fd("'", 2);
		mini->rtn = 255;
	}
	mini_free(mini);
	return (1);
}

int	syntax_check(t_shell *mini)
{
	t_token	*cp;

	cp = mini->token;
	while (cp)
	{
		if (quote_state(cp->s, ft_strlen(cp->s)))
			return (parse_err(mini, cp, 0));
		else if ((cp->type == PIPE && !cp->next) || ((cp->type == INPUT
					|| cp->type == HEREDOC || cp->type == OUTPUT
					|| cp->type == APPEND) && (!cp->next
					|| cp->next->type != ARG)))
			return (parse_err(mini, cp, 1));
		cp = cp->next;
	}
	return (0);
}
