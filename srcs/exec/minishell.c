/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:28:35 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/08 14:16:05 by jmathieu         ###   ########.fr       */
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
	if (is_redir(tk, 0))
		redir(mini, tk, i);
	if (tk && tk->type == BUILTIN)
	{
		g_sig = 0;
		b_process(mini);
		reset_std(mini);
		//exit(0);
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

void	child(t_shell *mini, t_token *tk, int i)
{
	if (i == 0)
	{
		dup2(mini->tab[i + 1][1], STDOUT_FILENO);
		close(mini->tab[i][0]);
	}
	else if (i == mini->ncmd - 1)
		dup2(mini->tab[i][0], STDIN_FILENO);
	else
	{
		dup2(mini->tab[i][0], STDIN_FILENO);
		dup2(mini->tab[i + 1][1], STDOUT_FILENO);
	}
	close_pipes(mini, i, 1);
	exec(mini, tk, i);
	exit(0);
}

void	minipipe(t_shell *mini, t_token *tk)
{
	int	i;

	i = 0;
	pipe_alloc(mini);
	g_sig = 300;
	if (hrdc_manager(mini))
		return ;
	i = 0;
	while (i < mini->ncmd)
	{
		mini->pid[i] = fork();
		if (mini->pid[i] < 0)
			err_manager(mini, tk, 2);
		if (mini->pid[i] == 0)
			child(mini, tk, i);
		tk = next_cmd(tk);
		i++;
	}
	i = -1;
	close_pipes(mini, i, 0);
	hrdc_close(mini, get_htab(mini, i), 0);
	while (++i < mini->ncmd)
		waitpid(mini->pid[i], &mini->rtn, 0);
	mini->rtn = WEXITSTATUS(mini->rtn);
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
