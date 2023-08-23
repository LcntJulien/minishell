/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:57:43 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/23 20:05:05 by jlecorne         ###   ########.fr       */
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

void	heredoc_handler(t_shell *mini, t_token *tk)
{
	t_hrdc	*hrdc;
	char	**tab;
	char	*tmp;
	int		i;

	hrdc = new_hrdc(tk);
	tab = ft_calloc(sizeof(char *), 100);
	tmp = NULL;
	i = 0;
	while (1)
	{
		tmp = readline("\033[0;35m\033[▸ \033[");
		if (tmp[0] && ft_strncmp(tmp, tk->s, ft_strlen(tmp)) == 0)
			break ;
		tab[i++] = tmp;
	}
	hrdc->content = malloc(sizeof(char *) * i + 1);
	if (!hrdc->content)
		return ;
	i = -1;
	while (tab[++i] != NULL)
		hrdc->content[i] = ft_strdup(tab[i]);
	hrdc->content[i] = NULL;
	add_hrdc(mini, hrdc);
	free(tab);
}

char	*hrdc_convert(t_shell *mini, char *s)
{
	char	*cur;
	int		len;
	int		i;

	cur = NULL;
	len = ft_strlen(s);
	i = -1;
	while (s && s[++i])
	{
		if (s[i] == '$' && !(is_quote(s) && quote_state(s, i) == 1))
		{
			cur = get_vname(s, i);
			s = rewrite(mini, s, cur, i);
			i += ft_strlen(s) - len;
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
