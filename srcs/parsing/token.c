/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:46:14 by jlecorne          #+#    #+#             */
/*   Updated: 2023/06/22 20:26:36 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	str_alloc(char *line, int *i)
{
	int	j;

	j = 0;
	while (line[*i + j])
	{
		if (line[*i + j] == ' ' && quote_state(line, *i + j) == 0)
			break ;
		j++;
	}
	return (j);
}

t_token	*new_token(char *line, int *i)
{
	int		j;
	t_token	*new;

	j = 0;
	new = malloc(sizeof(t_token));
	new->s = ft_calloc(sizeof(char), str_alloc(line, i) + 1);
	if (!new || !new->s)
		return (NULL);
	while (line[*i])
	{
		if (line[*i] == ' ' && quote_state(line, *i) == 0)
			break ;
		if (((line[*i] == '<' && line[*i + 2] == '<') || (line[*i] == '>'
					&& line[*i + 2] == '>')) && (line[*i - 1] != '<' || line[*i
				- 1] != '>'))
		{
			new->s[j++] = line[*i + 2];
			(*i)++;
		}
		else
			new->s[j++] = line[*i];
		(*i)++;
	}
	return (new);
}

void	*get_tokens(char *line)
{
	t_token	*prev;
	t_token	*token;
	int		i;

	prev = NULL;
	token = NULL;
	i = 0;
	space(line, &i);
	while (line[i])
	{
		token = new_token(line, &i);
		token->prev = prev;
		if (prev)
			prev->next = token;
		tk_type(token);
		prev = token;
		space(line, &i);
	}
	if (token)
		token->next = NULL;
	while (token && token->prev)
		token = token->prev;
	return (token);
}
