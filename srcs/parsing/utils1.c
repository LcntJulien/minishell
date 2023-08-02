/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:15:41 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/01 15:09:06 by jlecorne         ###   ########.fr       */
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
