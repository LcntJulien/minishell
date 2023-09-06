/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:45:27 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/05 18:38:44 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	do_redirin(t_shell *mini, t_token *cur, int i)
{
	if (cur && cur->prev->type == INPUT)
	{
		if (mini->in >= 0)
			close(mini->in);
		mini->in = open(cur->s, O_RDONLY);
		if (mini->in < 0)
			fds_err(mini, cur->s);
		if (mini->ncmd > 1)
			close(mini->tab[i][0]);
		dup2(mini->in, STDIN_FILENO);
	}
	else if (cur && cur->prev->type == HEREDOC)
	{
		if (mini->ncmd == 1)
		{
			if (solo_hrdc(mini, cur))
				return (1);
		}
		else
		{
			close(mini->tab[i][0]);
			dup2(mini->htab[get_htab(mini, i)][0], STDIN_FILENO);
		}
	}
	return (0);
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

int	redirin(t_shell *mini, t_token *tk, int i)
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
	{
		mini->rdr = 1;
		if (do_redirin(mini, cur, i))
			return (1);
	}
	return (0);
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
		mini->rdr += 2;
		do_redirout(mini, cur, i);
		close_output(tk, cur);
	}
}

int	redir(t_shell *mini, t_token *tk, int i)
{
	if (is_redir(tk, 1))
		if (redirin(mini, tk, i))
			return (1);
	if (is_redir(tk, 2))
		redirout(mini, tk, i);
	return (0);
}
