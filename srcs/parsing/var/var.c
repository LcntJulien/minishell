/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:08:47 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/24 16:16:06 by jlecorne         ###   ########.fr       */
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
		if (!s[i] || s[i] == ' ' || s[i] == '\'' || s[i] == '\"' || s[i] == '$')
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
			iter = get_nvar(mini, cur);
			tmp = rewrite(mini, tk->s, cur, i);
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
		if (s[i] == '$' && s[i + 1] && s[i + 1] != ' ' && s[i + 1] != '$' && s[i
				+ 1] != '_')
			return (1);
	return (0);
}
