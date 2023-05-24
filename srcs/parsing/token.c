/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:46:14 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/24 19:53:08 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
A noter pour tk_type():
 -- après echo, si plusieurs ARG se suivent sans qu'il n'y ai de STRING, ils
 	doivent être interprétés comme STRING -> postprocess à ajouter dans minishell()
 -- après une redirection un ARG est propablement un FILE -> postprocess à ajouter
	dans minishell() ou parse()
 -- les bonus necessiteront d'ajouet aux WC (wildcards) type
 -- une déclration de variable sera reconnue comme CMD -> postprocess à ajouter
	dans minishell() ou parse()
*/
void	tk_type(t_token *token)
{
	if (token->s[0] == '$')
		token->type = VAR;
	else if (token->s[0] == '\'' || token->s[0] == '\"')
		token->type = STRING;
	else if (ft_strncmp(token->s, "|", ft_strlen(token->s)) == 0)
		token->type = PIPE;
	else if (ft_strncmp(token->s, "<", ft_strlen(token->s)) == 0)
		token->type = INPUT;
	else if (ft_strncmp(token->s, ">", ft_strlen(token->s)) == 0)
		token->type = OUTPUT;
	else if (ft_strncmp(token->s, ">>", ft_strlen(token->s)) == 0)
		token->type = APPEND;
	else if (ft_strncmp(token->s, "<<", ft_strlen(token->s)) == 0)
		token->type = HEREDOC;
	else if (token->prev == NULL || token->prev->type == PIPE
			|| (token->prev->prev && token->prev->prev->type >= INPUT))
		token->type = CMD;
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
