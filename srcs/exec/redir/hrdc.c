/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hrdc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:57:43 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/25 10:08:36 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	add_hrdc(t_shell *mini, t_hrdc *hrdc)
{
	t_hrdc	*cp;

	cp = mini->hrdc;
	if (cp == NULL)
		mini->hrdc = hrdc;
	else
	{
		while (cp->next != NULL)
			cp = cp->next;
		cp->next = hrdc;
	}
}

t_hrdc	*new_hrdc(t_token *tk)
{
	t_hrdc	*hrdc;

	hrdc = malloc(sizeof(t_hrdc));
	if (!hrdc)
		return (NULL);
	hrdc->idx = tk->idx;
	hrdc->content = NULL;
	hrdc->next = NULL;
	return (hrdc);
}

int	heredoc_handler(t_shell *mini, t_token *tk)
{
	t_hrdc	*hrdc;
	char	**tab;
	char	*tmp;
	int		i;

	hrdc = new_hrdc(tk);
	tab = ft_calloc(sizeof(char *), 100);
	tmp = NULL;
	i = 0;
	g_sig = 2;
	while (1)
	{
		if (g_sig == 3)
			return (255);
		if (g_sig == 4)
			return (hrdc->idx);
		tmp = readline("\033[0;35m\033[1m▸ \033[0m");
		if (!tmp || (tmp &&
			tmp[0] && ft_strncmp(tmp, tk->s, ft_strlen(tmp)) == 0))
			break ;
		tab[i++] = tmp;
	}
	if (hrdc_filler(mini, hrdc, tab, i))
		return (255);
	free(tab);
	return (0);
}

char	*hrdc_convert(t_shell *mini, char *s)
{
	char	*cur;
	char	*tmp;
	char	*iter;
	int		i;

	cur = NULL;
	tmp = NULL;
	iter = NULL;
	i = -1;
	while (s && s[++i])
	{
		if (s[i] == '$' && !(is_quote(s) && quote_state(s, i) == 1))
		{
			cur = get_vname(s, i);
			iter = get_nvar(mini, cur);
			tmp = rewrite(mini, s, cur, i);
			free(s);
			s = tmp;
			i += (ft_strlen(iter) - 1);
			free2(cur, iter);
		}
	}
	return (s);
}

void	hrdc_syntax(t_shell *mini)
{
	t_hrdc	*cp;
	int		i;

	cp = mini->hrdc;
	i = -1;
	while (cp)
	{
		while (cp->content[++i])
		{
			if (contain_var(cp->content[i]))
				cp->content[i] = hrdc_convert(mini, cp->content[i]);
		}
		cp = cp->next;
	}
}
