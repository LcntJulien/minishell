/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:52:52 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/15 15:59:54 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	solo_hrdc(t_shell *mini, t_token *cur)
{
	pid_t	pid;

	signals_b_hrdc();
	pid = fork();
	if (pid < 0)
		err_manager(mini, NULL, 2);
	else if (!pid)
		solo_hrdc_filler(mini, cur);
	waitpid(pid, &mini->rtn, 0);
	mini->rtn = WEXITSTATUS(mini->rtn);
	printf("mini->rtn = %d\n", mini->rtn);
	if (mini->rtn)
		exit(mini->rtn);
}

// void	solo_hrdc(t_shell *mini, t_token *cur)
// {
// 	int		status;
// 	pid_t	pid;

// 	status = 0;
// 	alloc_htab(mini, 1);
// 	pid = fork();
// 	if (pid < 0)
// 		err_manager(mini, cur, 2);
// 	if (!pid)
// 	{
// 		g_sig = 2;
// 		solo_hrdc_filler(mini, cur);
// 		exit(0);
// 	}
// 	waitpid(pid, &status, 0);
// 	g_sig = 1;
// 	if (status == 256)
// 		mini->rtn = 1;
// 	if (status != 0)
// 		mini_free(mini);
// }

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
