/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:28:35 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/15 17:56:05 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	close_pipes(mini, tk, i, 1);
	redir_close(mini, tk);
	exec(mini, tk, i);
}

void	close_child(t_shell *mini, int i)
{
	if (i >= 0)
	{
		if (i == 0)
			close(mini->tab[i + 1][1]);
		else if (i != 0 && i != mini->ncmd - 1)
		{
			close(mini->tab[i][0]);
			close(mini->tab[i + 1][1]);
		}
	}
}

void	minipipe(t_shell *mini, t_token *tk)
{
	pid_t	pid;
	int		i;

	i = -1;
	g_sig = 1;
	piped_sig();
	pipe_alloc(mini);
	while (++i < mini->ncmd && g_sig <= 1)
	{
		pid = fork();
		if (pid == -1)
			err_manager(mini, NULL, 2);
		else if (!pid)
			child(mini, tk, i);
		close_child(mini, i - 1);
		waitpid(pid, &mini->rtn, 0);
		mini->rtn = WEXITSTATUS(mini->rtn);
		if (mini->rtn != 0)
			break ;
		tk = next_cmd(tk);
	}
	if (g_sig == 300)
		mini->rtn = 130;
	if (g_sig == 301)
		mini->rtn = 131;
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
