/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:57:29 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/28 17:00:06 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_hrdc(t_shell *mini)
{
	t_hrdc	*cp;
	t_hrdc	*tmp;
	int		i;

	cp = mini->hrdc;
	tmp = NULL;
	i = -1;
	if (cp)
	{
		while (cp)
		{
			tmp = cp->next;
			if (cp->content)
			{
				while (cp->content[++i])
					free(cp->content[i]);
				cp->content = NULL;
			}
			free(cp);
			cp = tmp;
		}
		mini->hrdc = NULL;
	}
}

void	free_token(t_shell *mini)
{
	t_token	*cpy;
	t_token	*tmp;

	cpy = mini->token;
	tmp = NULL;
	while (cpy && cpy != NULL)
	{
		tmp = cpy->next;
		if (cpy->s != NULL)
		{
			free(cpy->s);
			cpy->s = NULL;
		}
		free(cpy);
		cpy = tmp;
	}
	mini->token = NULL;
}

void	free_args(t_shell *mini)
{
	int	i;

	i = 0;
	if (mini->args)
	{
		while (mini->args[i])
			free(mini->args[i++]);
		free(mini->args);
		mini->args = NULL;
	}
}

void	free_pipe(t_shell *mini)
{
	int	i;

	i = 0;
	if (mini->tab)
	{
		while (i < mini->ncmd)
			free(mini->tab[i++]);
		free(mini->tab);
		mini->tab = NULL;
	}
}

void	free_paths(t_shell *mini)
{
	int	i;

	i = 0;
	if (mini->paths)
	{
		while (mini->paths[i])
			free(mini->paths[i++]);
		free(mini->paths);
		mini->paths = NULL;
	}
}
