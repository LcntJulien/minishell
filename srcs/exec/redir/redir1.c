/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:52:52 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/05 18:38:54 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	solo_hrdc(t_shell *mini, t_token *cur)
{
	int		status;
	pid_t	pid;

	status = 0;
	alloc_htab(mini, 1);
	pid = fork();
	if (pid < 0)
		err_manager(mini, cur, 2);
	if (!pid)
	{
		g_sig = 2;
		solo_hrdc_filler(mini, cur);
		close(mini->htab[0][1]);
		exit(0);
	}
	waitpid(pid, &status, 0);
	g_sig = 1;
	if (status == 256)
		mini->rtn = 1;
	if (status != 0)
	{
		mini_free(mini);
		return (1);
	}
	dup2(mini->htab[0][0], STDIN_FILENO);
	return (0);
}

int	is_redir(t_token *tk, int mode)
{
	t_token	*cp;
	int		in;
	int		out;

	cp = tk;
	in = 0;
	out = 0;
	while (cp && cp->prev && cp->prev->type != PIPE)
		cp = cp->prev;
	while (cp && cp->type != PIPE)
	{
		if (cp->type == INPUT || cp->type == HEREDOC)
			in++;
		if (cp->type == OUTPUT || cp->type == APPEND)
			out++;
		cp = cp->next;
	}
	if (!mode && (in || out))
		return (1);
	if (mode == 1 && in)
		return (1);
	if (mode == 2 && out)
		return (1);
	return (0);
}

t_token	*del_arg(t_token *tk)
{
	t_token	*tmp;

	tmp = tk;
	if (tk->prev && tk->next)
	{
		tmp = tk->next;
		tmp->prev = tk->prev;
		tk->prev->next = tmp;
	}
	else if (tk->next)
	{
		tmp = tk->next;
		tmp->prev = NULL;
	}
	else if (tk->prev)
	{
		tmp = tk->prev;
		tmp->next = NULL;
	}
	if (tk)
		free(tk);
	tk = NULL;
	return (tmp);
}

t_token	*del_redir(t_token *tk)
{
	tk = del_arg(tk);
	tk = del_arg(tk);
	return (tk);
}

void	args_redir(t_shell *mini, t_token *tk)
{
	t_token	*cp;
	int		i;

	cp = tk;
	i = 0;
	while (cp && cp->type != PIPE)
	{
		while (cp->type == INPUT || cp->type == HEREDOC || cp->type == OUTPUT
			|| cp->type == APPEND)
			cp = del_redir(cp);
		if (!cp->next)
			break ;
		cp = cp->next;
	}
	while (cp && cp->prev && cp->prev->type != PIPE)
		cp = cp->prev;
	mini->args = args_alloc(cp);
	while (cp && cp->type != PIPE)
	{
		mini->args[i++] = cp->s;
		cp = cp->next;
	}
	mini->args[i] = NULL;
}
