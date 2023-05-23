/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:46:14 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/23 20:41:17 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	tk_type(t_token *token)
{
	if (token->prev == NULL || token->prev->type >= HEREDOC)
		token->type = CMD;
	else if (token->s[0] == '$')
		token->type = VAR;
	else if (ft_strncmp(token->s, "<", ft_strlen(token->s)) == 0)
		token->type = INPUT;
	else if (ft_strncmp(token->s, ">", ft_strlen(token->s)) == 0)
		token->type = OUTPUT;
	else if (token->s[0] == '\''|| token->s[0] == '\"')
		token->type = STRING;
	else if (ft_strncmp(token->s, ">>", ft_strlen(token->s)) == 0)
		token->type = APPEND;
	else if (ft_strncmp(token->s, "<<", ft_strlen(token->s)) == 0)
		token->type = HEREDOC;
	else if (ft_strncmp(token->s, "|", ft_strlen(token->s)) == 0)
		token->type = PIPE;
	else
		token->type = ARG;
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

t_token	*new_token(char *line, int *i)
{
	int		j;
	t_token	*new;

	j = 0;
	if (!(new = malloc(sizeof(t_token))) ||
		!(new->s = malloc(sizeof(char) * str_alloc(line, i) + 1)))
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
	new->s[j] = 0;
	return (new);
}

void	*get_tokens(char *line)
{
	t_token *prev;
	t_token *token;
	int i;

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
