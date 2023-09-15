/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:28:35 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/15 16:57:24 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	reset_std(t_shell *mini)
{
	dup2(mini->o_in, STDIN_FILENO);
	dup2(mini->o_out, STDOUT_FILENO);
}

t_token	*prev_cmd(t_token *tk)
{
	t_token	*cp;

	cp = tk;
	if (cp && cp->prev)
	{
		cp = cp->prev;
		while (cp && cp->type != CMD && cp->type != BUILTIN)
			cp = cp->prev;
	}
	return (cp);
}

t_token	*next_cmd(t_token *tk)
{
	if (tk && tk->next)
	{
		tk = tk->next;
		while (tk && tk->type != CMD && tk->type != BUILTIN)
			tk = tk->next;
	}
	return (tk);
}

void	exec(t_shell *mini, t_token *tk, int i)
{
	if (mini->ncmd == 1 && is_redir(tk, 0))
		redir(mini, tk, i);
	if (tk && tk->type == BUILTIN)
	{
		g_sig = 0;
		b_process(mini);
		reset_std(mini);
		if (mini->ncmd > 1)
			exit(0);
	}
	else if (tk)
	{
		get_args(mini, tk);
		mini->cmd = get_cmd(mini);
		if (!mini->cmd)
			err_manager(mini, tk, 0);
		execve(mini->cmd, mini->args, mini->env);
		exit(EXIT_FAILURE);
	}
}

void	redir_close(t_shell *mini, t_token *tk)
{
	close(mini->fd[1]);
	if (!is_hrdc(tk))
		close(mini->fd[0]);
	if (!is_redir(tk, 1))
		close(mini->in);
	if (!is_redir(tk, 2))
		close(mini->out);
}

void	child(t_shell *mini, t_token *tk, int i)
{
	if (is_redir(tk, 0))
		redir(mini, tk, i);
	if (i == 0 && !is_redir(tk, 2))
		dup2(mini->tab[i + 1][1], STDOUT_FILENO);
	else if (i == mini->ncmd - 1 && !is_redir(tk, 1))
		dup2(mini->tab[i][0], STDIN_FILENO);
	else if (i != 0 && i != mini->ncmd - 1)
	{
		if (!is_redir(tk, 1))
			dup2(mini->tab[i][0], STDIN_FILENO);
		if (!is_redir(tk, 2))
			dup2(mini->tab[i + 1][1], STDOUT_FILENO);
	}
	close_pipes(mini, tk, i, 0);
	redir_close(mini, tk);
	exec(mini, tk, i);
}

void	close_child(t_shell *mini, t_token *tk, int i)
{
	if (i >= 0)
	{
		if (i == 0 && !is_redir(tk, 2))
		{
			fprintf(stderr, "close(mini->tab[%d + 1][1]);\n", i);
			close(mini->tab[i + 1][1]);
		}
		else if (i != 0 && i != mini->ncmd - 1)
		{
			if (!is_redir(tk, 1))
			{
				fprintf(stderr, "close(mini->tab[%d][0]);\n", i);
				close(mini->tab[i][0]);
			}
			if (!is_redir(tk, 2))
			{
				fprintf(stderr, "close(mini->tab[%d + 1][1]);\n", i);
				close(mini->tab[i + 1][1]);
			}
		}
		if (is_redir(tk, 2))
		{
			fprintf(stderr, "close(mini->out);\n");
			close(mini->out);
		}
		if (is_redir(tk, 1) && !is_hrdc(tk))
		{
			fprintf(stderr, "close(mini->in);\n");
			close(mini->in);
		}
		else if (is_redir(tk, 1) && !is_hrdc(tk))
		{
			fprintf(stderr, "close(mini->fd[0]);\n");
			close(mini->fd[0]);
		}
	}
}

void	minipipe(t_shell *mini, t_token *tk)
{
	pid_t	pid;
	int		i;

	i = -1;
	pipe_alloc(mini);
	while (++i < mini->ncmd)
	{
		pid = fork();
		if (pid == -1)
			err_manager(mini, NULL, 2);
		else if (!pid)
			child(mini, tk, i);
		close_child(mini, prev_cmd(tk), i - 1);
		waitpid(pid, &mini->rtn, 0);
		mini->rtn = WEXITSTATUS(mini->rtn);
		if (mini->rtn != 0)
			break ;
		tk = next_cmd(tk);
	}
}

void	minishell(t_shell *mini)
{
	t_token	*tk;
	pid_t	pid;

	tk = mini->token;
	mini->ncmd = nb_cmd(mini);
	get_paths(mini);
	if (tk && tk->idx == 0 && tk->type != CMD && tk->type != BUILTIN)
		tk = next_cmd(tk);
	if (mini->ncmd > 1)
		minipipe(mini, tk);
	else if (mini->ncmd == 1)
	{
		if (tk && tk->type == BUILTIN)
			exec(mini, tk, 0);
		else
		{
			g_sig = 1;
			pid = fork();
			if (pid < 0)
				err_manager(mini, tk, 2);
			else if (pid == 0)
				exec(mini, tk, 0);
			waitpid(pid, &mini->rtn, 0);
			mini->rtn = WEXITSTATUS(mini->rtn);
		}
	}
}
