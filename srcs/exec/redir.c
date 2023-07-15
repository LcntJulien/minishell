/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:45:27 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/14 16:27:39 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redir(t_shell *mini, t_token *tk, int i)
{
	(void)mini;
	(void)tk;
	(void)i;
}

void	redirin(t_shell *mini, t_token *tk, int i)
{
	t_token	*cp;
	int		j;
	int		k;
	int		input;
	int		heredoc;

	cp = tk;
	j = 0;
	k = 0;
	input = 0;
	heredoc = 0;
	while (cp && cp->type != PIPE)
	{
		if (cp->type == INPUT)
			input++;
		if (cp->type == HEREDOC)
			heredoc++;
		cp = cp->next;
	}
	cp = tk;
	while (cp && cp->type != PIPE)
	{
		if (cp->type == INPUT && j == input)
			redir(mini, cp->next, i);
		else if (cp->type == INPUT && j < input)
			j++;
		cp = cp->next;
	}
	cp = tk;
	while (cp && cp->type != PIPE)
	{
		if (cp->type == HEREDOC && k == heredoc)
			redir(mini, cp->next, i);
		else if (cp->type == HEREDOC && k < heredoc)
			k++;
		cp = cp->next;
	}
}

void	redirout(t_shell *mini, t_token *tk, int i)
{
	(void)mini;
	(void)tk;
	(void)i;
}

void	is_redir(t_shell *mini, t_token *tk, int tab[11], int i)
{
	t_token	*cpy;

	cpy = tk;
	while (cpy && cpy->type != PIPE)
	{
		if (cpy->type == INPUT)
			tab[INPUT]++;
		else if (cpy->type == OUTPUT)
			tab[OUTPUT]++;
		else if (cpy->type == APPEND)
			tab[APPEND]++;
		else if (cpy->type == HEREDOC)
			tab[HEREDOC]++;
		cpy = cpy->next;
	}
	if (tab[INPUT] >= 1 || tab[HEREDOC] >= 1 || tab[OUTPUT] >= 1
		|| tab[APPEND] >= 1)
	{
		if (tab[INPUT] >= 1 || tab[HEREDOC] >= 1)
			redirin(mini, tk, i);
		if (tab[OUTPUT] >= 1 || tab[APPEND] >= 1)
			redirout(mini, tk, i);
	}
}
