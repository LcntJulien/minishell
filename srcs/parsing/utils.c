/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:27:35 by jlecorne          #+#    #+#             */
/*   Updated: 2023/06/07 16:01:08 by jlecorne         ###   ########.fr       */
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

void	space(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t') || (line[*i] == '\r'
			|| line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
}

void	listfree(t_token *tk)
{
	t_token	*tmp;

	tmp = NULL;
	while (tk->next != NULL)
		tk = tk->next;
	while (tk->prev != NULL)
	{
		tmp = tk;
		free(tmp->s);
		free(tmp);
		tmp = NULL;
		tk = tk->prev;
	}
	free(tk);
	tk = NULL;
}

void	clean_tokens(t_token *tk)
{
	char	*cpy;

	while (tk)
	{
		if ((tk->type == CMD || tk->type == OPTION || tk->type == BUILTIN)
			&& (tk->s[0] == '\'' || tk->s[0] == '\"'))
		{
			cpy = ft_strdup(tk->s);
			free(tk->s);
			tk->s = NULL;
			tk->s = ft_substr(cpy, 1, ft_strlen(cpy) - 2);
		}
		tk = tk->next;
	}
}

void	convert_var(t_token *tk, t_shell *mini)
{
	char	*cpy;
	int		i;

	cpy = ft_substr(tk->s, 1, ft_strlen(tk->s) - 1);
	free(tk->s);
	tk->s = NULL;
	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(cpy, mini->env[i], ft_strlen(cpy)) == 0)
		{
			cpy = ft_substr(mini->env[i], ft_strlen(cpy) + 1,
					ft_strlen(mini->env[i]) - ft_strlen(cpy) + 1);
			tk->s = cpy;
			break ;
		}
		i++;
	}
	free(cpy);
}
