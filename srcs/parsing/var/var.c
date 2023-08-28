/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:08:47 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/28 15:11:18 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*get_vname(char *s, int idx)
{
	char	*var;
	int		len;
	int		i;

	var = NULL;
	len = 0;
	i = idx;
	while (s[++i])
	{
		if (!s[i] || s[i] == ' ' || s[i] == '\'' || s[i] == '\"')
			break ;
		len++;
	}
	var = ft_substr(s, (idx + 1), len);
	return (var);
}

void	convert_var(t_shell *mini, t_token *tk)
{
	char	*cur;
	char	*tmp;
	char	*iter;
	int		i;

	cur = NULL;
	tmp = NULL;
	iter = NULL;
	i = -1;
	while (tk->s && tk->s[++i])
	{
		if (tk->s[i] == '$' && !(is_quote(tk->s) && quote_state(tk->s, i) == 1))
		{
			cur = get_vname(tk->s, i);
			printf("cur = %s\n", cur);
			if (tk->s[i + 1] != '$' && tk->s[i + 1] != '_' && tk->s[i + 1] != '?')
			{
				iter = get_nvar(mini, cur);
				printf("iter = %s\n", iter);
				tmp = rewrite(mini, tk->s, cur, i);
				printf("tmp = %s\n", tmp);
			}
			else
			{
				iter = other_variable(mini, tk, i + 1);
				printf("other iter = %s\n", iter);
				tmp = rewrite2(mini, tk->s, iter, i);
				printf("other tmp = %s\n", tmp);
		}
		free(tk->s);
		tk->s = tmp;
		i += (ft_strlen(iter) - 1);
		free2(cur, iter);
		}
	}
}

int	contain_var(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '$' && s[i + 1] && s[i + 1] != ' ' && s[i + 1] != '$' && s[i
				+ 1] != '_' && s[i + 1] != '?')
			return (1);
		else if (s[i] == '$' && s[i + 1] && (s[i + 1] == '$' || s[i + 1] == '_'
			|| s[i + 1] == '?'))
			return (1);
	}
	return (0);
}
