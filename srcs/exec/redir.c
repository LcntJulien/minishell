/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:45:27 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/25 14:51:54 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	do_redirin(t_shell *mini, t_token *cur, int i)
{
	t_hrdc	*cp;
	int		j;

	cp = mini->hrdc;
	j = -1;
	if (cur && cur->prev->type == INPUT)
	{
		if (mini->in >= 0)
			close(mini->in);
		mini->in = open(cur->s, O_RDONLY);
		if (mini->in < 0)
			fds_err(mini, cur->s);
		dup2(mini->in, STDIN_FILENO);
		close(mini->tab[i][0]);
	}
	else if (cur && cur->prev->type == HEREDOC)
	{
		dup2(mini->tab[i][1], STDOUT_FILENO);
		while (cp->next && cp->idx != cur->idx)
			cp = cp->next;
		while (cp->content[++j])
			ft_putendl_fd(cp->content[j], STDOUT_FILENO);
		dup2(mini->tab[i][0], STDIN_FILENO);
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
	if (i < mini->ncmd - 1)
		close(mini->tab[i + 1][1]);
	dup2(mini->out, STDOUT_FILENO);
}

void	redirin(t_shell *mini, t_token *tk, int i)
{
	t_token	*cp;
	t_token	*cur;

	cp = tk;
	cur = NULL;
	while (cp->prev != NULL && cp->prev->type != PIPE)
		cp = cp->prev;
	while (cp->next && cp->type != PIPE)
	{
		if (cp->type == INPUT || cp->type == HEREDOC)
			cur = cp->next;
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
			cur = cp->next;
		cp = cp->next;
	}
	while (cp->prev != NULL && cp->prev->type != PIPE)
		cp = cp->prev;
	if (cur != NULL)
	{
		clear_files(mini, cp, cur->s);
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
