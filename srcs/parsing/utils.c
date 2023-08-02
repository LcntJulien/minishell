/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:27:35 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/01 17:02:58 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	space(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t') || (line[*i] == '\r'
			|| line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
}

int	is_sep(char *line, int i)
{
	if (ft_strchr("<>|", line[i]) && quote_state(line, i) == 0)
		return (1);
	else
		return (0);
}

int	is_quote(t_token *tk)
{
	int	i;
	int	r;

	i = -1;
	r = 0;
	while (tk->s[++i])
		if (tk->s[i] == '\'' || tk->s[i] == '\"')
			r++;
	return (r);
}

int	quote_state(char *line, int idx)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (line[i] && i <= idx)
	{
		if (quote == 0 && line[i] == '\'')
			quote = 1;
		else if (quote == 0 && line[i] == '\"')
			quote = 2;
		else if (quote == 1 && line[i] == '\'')
			quote = 0;
		else if (quote == 2 && line[i] == '\"')
			quote = 0;
		i++;
	}
	return (quote);
}

int	syntax_check(t_shell *mini, int mode)
{
	t_token	*cp;

	cp = mini->token;
	while (cp)
	{
		if (!mode)
		{
			if (is_quote(cp) && (((cp->s[0] == '\'' || cp->s[0] == '\"')
							&& cp->s[0] != cp->s[ft_strlen(cp->s) - 1])
							|| ((cp->s[ft_strlen(cp->s) - 1] == '\''
							|| cp->s[ft_strlen(cp->s) - 1] == '\"')
						&& cp->s[ft_strlen(cp->s) - 1] != cp->s[0])))
				return (parse_err(mini, cp, 0));
		}
		else
		{
			if ((cp->type == PIPE && !cp->next) || ((cp->type == INPUT
						|| cp->type == HEREDOC || cp->type == OUTPUT
						|| cp->type == APPEND) && (!cp->next
						|| cp->next->type != ARG)))
				return (parse_err(mini, cp, 1));
		}
		cp = cp->next;
	}
	return (0);
}
