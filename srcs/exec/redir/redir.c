/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:45:27 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/24 11:49:54 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	do_redirin(t_shell *mini, t_token *cur, int i)
{
	if (cur && cur->prev->type == INPUT)
	{
		if (mini->in >= 0)
			close(mini->in);
		mini->in = open(cur->s, O_RDONLY);
		if (mini->in < 0)
			fds_err(mini, cur->s);
		dup2(mini->in, STDIN_FILENO);
		if (mini->ncmd > 1)
			close(mini->tab[i][0]);
	}
	else if (cur && cur->prev->type == HEREDOC)
	{
		if (mini->ncmd > 1)
		{
			close(mini->tab[i][0]);
			if (i < mini->ncmd - 1)
				close(mini->tab[i + 1][1]);
		}
		redir_hrdc(mini, cur);
		if (mini->ncmd > 1 && i < mini->ncmd - 1)
			dup2(mini->tab[i + 1][1], STDOUT_FILENO);
	}
}

void	do_redirout(t_shell *mini, t_token *cur, int i)
{
	if (cur->prev->type == OUTPUT)
		mini->out = open(cur->s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (cur->prev->type == APPEND)
		mini->out = open(cur->s, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (mini->out < 0)
		fds_err(mini, cur->s);
	if (mini->ncmd > 1 && i < mini->ncmd - 1)
		close(mini->tab[i + 1][1]);
	dup2(mini->out, STDOUT_FILENO);
}

void	redirin(t_shell *mini, t_token *tk, int i)
{
	t_token	*cp;
	t_token	*cur;

	cp = tk;
	cur = NULL;
	while (cp->prev && cp->prev->type != PIPE)
		cp = cp->prev;
	while (cp->next && cp->type != PIPE)
	{
		if (cp->next && (cp->type == INPUT || cp->type == HEREDOC))
			cur = cp->next;
		cp = cp->next;
	}
	if (cur)
		do_redirin(mini, cur, i);
}

void	redirout(t_shell *mini, t_token *tk, int i)
{
	t_token	*cp;
	t_token	*cur;

	cp = tk;
	cur = NULL;
	while (cp->prev && cp->prev->type != PIPE)
		cp = cp->prev;
	while (cp && cp->type != PIPE)
	{
		if (cp->next && (cp->type == OUTPUT || cp->type == APPEND))
			cur = cp->next;
		cp = cp->next;
	}
	if (cur)
	{
		do_redirout(mini, cur, i);
		close_output(tk, cur);
	}
}

void	redir(t_shell *mini, t_token *tk, int i)
{
	if (is_redir(tk, 1))
		redirin(mini, tk, i);
	if (is_redir(tk, 2))
		redirout(mini, tk, i);
}