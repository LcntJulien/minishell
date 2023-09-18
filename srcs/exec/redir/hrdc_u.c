/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hrdc_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:08:10 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/18 16:13:35 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_hrdc(t_token *tk)
{
	t_token	*cp;
	t_token	*cur;

	cp = tk;
	cur = NULL;
	while (cp && cp->prev && cp->prev->type != PIPE)
		cp = cp->prev;
	while (cp && cp->next && cp->type != PIPE)
	{
		if (cp->next && (cp->type == INPUT || cp->type == HEREDOC))
			cur = cp->next;
		cp = cp->next;
	}
	if (cur && cur->prev->type == HEREDOC)
		return (1);
	return (0);
}

int	nb_hrdc(t_shell *mini)
{
	t_token	*cp;
	int		i;
	int		r;

	cp = mini->token;
	i = -1;
	r = 0;
	while (++i < mini->ncmd)
	{
		if (is_redir(cp, 1) && is_hrdc(cp))
			r++;
		cp = next_cmd(cp);
	}
	return (r);
}
