/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:46:14 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/31 19:42:19 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	token_idx(t_shell *mini)
{
	t_token	*cp;
	int		i;

	cp = mini->token;
	i = 0;
	while (cp != NULL)
	{
		cp->idx = i++;
		cp = cp->next;
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

void	clean_tokens(t_token *tk)
{
	t_token	*cp;
	char	*s;

	cp = tk;
	s = NULL;
	while (cp)
	{
		if (is_quote(cp) /*&& ((cp->type == VAR && valid_var(cp))
				|| (cp->type != ARG && cp->type != VAR && !quote_state(cp->s,
						ft_strlen(cp->s) - 1)) || (cp->type == ARG
					&& is_quote(cp) > 1))*/
		)
		{
			s = ft_strdup(cp->s);
			free(cp->s);
			cp->s = NULL;
			cp->s = clean_s(s);
		}
		cp = cp->next;
	}
	free(s);
	free(cp);
}
