/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:45:27 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/18 02:06:59 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	do_redirin(t_shell *mini, t_token *cur, int i)
{
	(void)mini;
	(void)cur;
	(void)i;
}

void	do_redirout(t_shell *mini, t_token *cur, int i)
{
	(void)mini;
	(void)cur;
	(void)i;
}

void	redirin(t_shell *mini, t_token *tk, int i)
{
	t_token	*cp;
	t_token	*cur;

	cp = tk;
	cur = NULL;
	while (cp->prev != NULL && cp->prev->type != PIPE)
		cp = cp->prev;
	while (cp && cp->type != PIPE)
	{
		if (cp->type == INPUT || cp->type == HEREDOC)
			cur = cp;
		cp = cp->next;
	}
	if (cur != NULL)
		do_redirin(mini, cur, i);
}

void	redirout(t_shell *mini, t_token *tk, int i)
{
	t_token	*cp;
	t_token	*cur;

	cp = tk;
	cur = NULL;
	while (cp->prev != NULL && cp->prev->type != PIPE)
		cp = cp->prev;
	while (cp && cp->type != PIPE)
	{
		if (cp->type == OUTPUT || cp->type == APPEND)
			cur = cp;
		cp = cp->next;
	}
	while (cp->prev != NULL && cp->prev->type != PIPE)
		cp = cp->prev;
	if (cur != NULL)
	{
		// clear_files(mini, cp);
		do_redirout(mini, cur, i);
	}
}

void	redir(t_shell *mini, t_token *tk, int tab[11], int i)
{
	t_token	*cp;

	cp = tk;
	while (cp && cp->type != PIPE)
	{
		if (cp->type == INPUT)
			tab[INPUT]++;
		else if (cp->type == OUTPUT)
			tab[OUTPUT]++;
		else if (cp->type == APPEND)
			tab[APPEND]++;
		else if (cp->type == HEREDOC)
			tab[HEREDOC]++;
		cp = cp->next;
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
