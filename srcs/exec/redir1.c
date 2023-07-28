/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:57:43 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/28 19:17:14 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_hrdc(t_shell *mini, t_hrdc *hrdc)
{
	t_hrdc	*cp;
	t_hrdc	*tmp;

	cp = hrdc;
	tmp = NULL;
	if (mini->hrdc != NULL)
	{
		while (cp != NULL)
		{
			tmp = cp->next;
			if (cp->content != NULL)
				free_tab(cp->content);
			free(cp);
			cp = tmp;
		}
		mini->hrdc = NULL;
	}
}

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

	(void)mini;
	hrdc = new_hrdc(tk);
	tab = ft_calloc(sizeof(char *), 50);
	tmp = NULL;
	i = 0;
	while (1)
	{
		tmp = readline("\033[0;35m\033[▸ \033[");
		if (ft_strncmp(tmp, tk->s, ft_strlen(tmp)) == 0)
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
}

void	hrdc_manager(t_shell *mini)
{
	t_token	*tk;

	tk = mini->token;
	while (tk->next != NULL)
	{
		if (tk->type == HEREDOC)
			heredoc_handler(mini, tk->next);
		tk = tk->next;
	}
}
