/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:35:06 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/17 14:36:20 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	reset_std(t_shell *mini)
{
	dup2(mini->o_in, STDIN_FILENO);
	dup2(mini->o_out, STDOUT_FILENO);
}

t_token	*prev_cmd(t_token *tk)
{
	t_token	*cp;

	cp = tk;
	if (cp && cp->prev)
	{
		cp = cp->prev;
		while (cp && cp->type != CMD && cp->type != BUILTIN)
			cp = cp->prev;
	}
	return (cp);
}

t_token	*next_cmd(t_token *tk)
{
	if (tk && tk->next)
	{
		tk = tk->next;
		while (tk && tk->type != CMD && tk->type != BUILTIN)
			tk = tk->next;
	}
	return (tk);
}
