/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:27:35 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/18 14:58:00 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	space(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t') || (line[*i] == '\r'
			|| line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
}

void	listfree(t_shell *mini, t_token *tk)
{
	t_token	*cpy;
	t_token	*tmp;

	cpy = tk;
	tmp = NULL;
	if (mini->token != NULL)
	{
		while (cpy != NULL)
		{
			tmp = cpy->next;
			free(cpy->s);
			cpy->s = NULL;
			free(cpy);
			cpy = tmp;
		}
		mini->token = NULL;
	}
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

void	convert_var(t_token *tk, t_shell *mini)
{
	char	*cpy;
	int		i;

	cpy = ft_strtrim(tk->s, "$");
	i = 0;
	if (mini->env)
	{
		while (mini->env[i])
		{
			if (ft_strncmp(cpy, mini->env[i], ft_strlen(cpy)) == 0)
			{
				cpy = ft_substr(mini->env[i], ft_strlen(tk->s),
						ft_strlen(mini->env[i]) - ft_strlen(tk->s));
				free(tk->s);
				tk->s = NULL;
				tk->s = ft_strdup(cpy);
				free(cpy);
				return ;
			}
			i++;
		}
	}
	free(cpy);
}
