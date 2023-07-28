/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:52:52 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/28 20:18:50 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redir_hrdc(t_shell *mini, t_token *cur)
{
	t_hrdc	*cp;
	int		j;

	cp = mini->hrdc;
	j = -1;
	fprintf(stderr, "%s\n", cp->content[0]);
	mini->in = open(HRDC, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (mini->in < 0)
		fds_err(mini, HRDC);
	while (cp->next && cp->idx != cur->idx)
	{
		fprintf(stderr, "token->idx: %d\nhrdc->idx: %d\n", cur->idx, cp->idx);
		cp = cp->next;
	}
	while (cp->content[++j])
		ft_putendl_fd(cp->content[j], mini->in);
	close(mini->in);
	mini->in = open(HRDC, O_RDONLY);
	dup2(mini->in, STDIN_FILENO);
}

int	is_redir(t_token *tk, int mode)
{
	t_token	*cp;
	int		in;
	int		out;

	cp = tk;
	in = 0;
	out = 0;
	while (cp->prev != NULL && cp->prev->type != PIPE)
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
