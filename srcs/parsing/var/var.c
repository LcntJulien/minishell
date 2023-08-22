/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:08:47 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/22 19:49:07 by jlecorne         ###   ########.fr       */
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
	int		len;
	int		i;

	cur = NULL;
	len = ft_strlen(tk->s);
	i = -1;
	while (tk->s && tk->s[++i])
	{
		if (tk->s[i] == '$' && !(is_quote(tk) && quote_state(tk->s, i) == 1))
		{
			cur = get_vname(tk->s, i);
			tk->s = rewrite(mini, tk->s, cur, i);
			i += ft_strlen(tk->s) - len;
		}
	}
	if (cur)
		free(cur);
}

int	contain_var(t_token *tk)
{
	char	*s;
	int		i;

	s = NULL;
	i = -1;
	while (tk->s[++i])
		if (tk->s[i] == '$' && tk->s[i + 1] && tk->s[i + 1] != ' ' && tk->s[i
			+ 1] != '$' && tk->s[i + 1] != '_')
			return (1);
	if (s)
		free(s);
	return (0);
}
