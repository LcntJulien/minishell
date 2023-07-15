/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:15:41 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/15 15:31:20 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_dollar(t_token *tk)
{
	int	i;

	i = -1;
	while (tk->s[++i])
		if (tk->s[i] == '$')
			return (1);
	return (0);
}

int	valid_var(t_token *tk)
{
	int	i;
	int	r;

	i = -1;
	r = 0;
	while (tk->s[++i])
		if (tk->s[i] == '$')
			r++;
	i = 0;
	while (tk->s[++i])
		if (tk->s[i] == '\'')
			return (0);
	return (r);
}

int	clean_alloc(char *s)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '\"')
			r++;
		else if (quote_state(s, i) && ((s[i] == '\'' && quote_state(s, i) == 2)
						|| (s[i] == '\"' && quote_state(s, i) == 1)))
			r++;
		i++;
	}
	return (r + 1);
}

char	*clean_s(char *s)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = clean_alloc(s);
	new = malloc(sizeof(char) * j);
	if (!new)
		return (NULL);
	j = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '\"')
			new[j++] = s[i];
		else if (quote_state(s, i) && ((s[i] == '\'' && quote_state(s, i) == 2)
						|| (s[i] == '\"' && quote_state(s, i) == 1)))
			new[j++] = s[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

void	clean_tokens(t_token *tk)
{
	t_token	*cpy;
	char	*s;

	cpy = tk;
	s = NULL;
	while (cpy)
	{
		if (is_quote(cpy) && ((cpy->type == VAR && valid_var(cpy))
				|| (cpy->type != ARG && cpy->type != VAR && !quote_state(cpy->s,
						ft_strlen(cpy->s) - 1)) || (cpy->type == ARG
					&& is_quote(cpy) > 1)))
		{
			s = ft_strdup(cpy->s);
			free(cpy->s);
			cpy->s = NULL;
			cpy->s = clean_s(s);
		}
		cpy = cpy->next;
	}
	free(s);
	free(cpy);
}
