/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:46:14 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/12 16:08:01 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	display_tokens(t_token *token)
{
	char	*tab[11];

	tab[0] = "CMD";
	tab[1] = "ARG";
	tab[2] = "VAR";
	tab[3] = "OPTION";
	tab[4] = "BUILTIN";
	tab[5] = "DECLAVAR";
	tab[6] = "PIPE";
	tab[7] = "INPUT";
	tab[8] = "OUTPUT";
	tab[9] = "APPEND";
	tab[10] = "HEREDOC";
	while (token)
	{
		if (token->s != NULL)
			fprintf(stderr, "%s --> %s\n", token->s, tab[token->type]);
		else
			fprintf(stderr, "|VIDE| --> %s\n", tab[token->type]);
		token = token->next;
	}
}

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

t_token	*new_token(char *line, int *i, int j)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->s = ft_calloc(sizeof(char), (str_alloc(line, i) + 1));
	if (!new->s)
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
		token = new_token(line, &i, 0);
		if (!token)
			return (NULL);
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
