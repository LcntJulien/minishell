/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:27:35 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/22 19:46:42 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	quote_state(char *line, int idx)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (line[i] && i < idx)
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (quote == 0 && line[i] == '\'')
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

int	is_sep(char *line, int i)
{
	if (i > 0 && line[i - 1] == '\\' && ft_strchr("<>|", line[i]))
		return (0);
	else if (ft_strchr("<>|", line[i]) && quote_state(line, i) == 0)
		return (1);
	else
		return (0);
}

void	space(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t') || (line[*i] == '\r'
			|| line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
}

void	listfree(t_token *token)
{
	t_token	*tmp;

	tmp = NULL;
	while (token->next != NULL)
		token = token->next;
	while (token->prev != NULL)
	{
		tmp = token;
		free(tmp->s);
		free(tmp);
		tmp = NULL;
		token = token->prev;
	}
	free(token);
	token = NULL;
}
