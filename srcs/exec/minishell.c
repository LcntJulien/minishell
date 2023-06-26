/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:28:35 by jlecorne          #+#    #+#             */
/*   Updated: 2023/06/26 21:29:03 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*next_cmd(t_token *tk)
{
	while (tk && tk->type != PIPE)
		tk = tk->next;
	if (tk && tk->type == PIPE)
		tk = tk->next;
	return (tk);
}

void	exec(t_shell *mini, t_token *tk)
{
	if (tk->type == BUILTIN)
		b_process(mini);
	else
	{
		mini->args = get_args(tk);
		mini->cmd = get_cmd(mini);
		if (!mini->cmd)
			err_manager();
		if (execve(mini->cmd, mini->args, mini->env) == -1)
			err_manager();
	}
}

void	child(t_shell *mini, t_token *tk, int *tab, int i)
{
	if (!is_redir(tk))
	{
		if (i == 0)
		{
			dup2(tab[i][0], STDIN_FILENO);
			dup2(tab[i][1], STDOUT_FILENO);
		}
		else if (i == mini->ncmd)
			dup2(tab[i][0], tab[i - 1][1]);
		else
		{
			dup2(tab[i][0], tab[i - 1][1]);
			dup2(tab[i][1], STDOUT_FILENO);
		}
		close_pipes(tab);
	}
	exec(mini, tk);
}

void	minipipe(t_shell *mini, t_token *tk)
{
	int		i;
	int		**tab[mini->ncmd][2];
	pid_t	*pid;

	i = 0;
	pid = malloc(sizeof(pid_t) * mini->ncmd);
	if (!mini->pid)
		err_manager();
	while (i < mini->ncmd)
	{
		if (pipe(tab[i]) < 0)
			err_manager();
		pid[i] = fork();
		if (pid[i] < 0)
			err_manager();
		if (pid[i] == 0)
			child(mini, tk, tab, i);
		tk = next_cmd(tk);
		i++;
	}
	close_pipes(mini);
	i = 0;
	while (i++ < mini->ncmd)
		waitpid(-1, &mini->status, 0);
	free_cpa(mini);
}

void	minishell(t_shell *mini)
{
	t_token	*tk;
	pid_t	pid;

	tk = mini->token;
	mini->ncmd = nb_cmd(mini);
	get_paths(mini);
	if (mini->ncmd > 1)
		minipipe(mini, tk, mini->ncmd);
	else
	{
		pid = fork();
		if (pid < 0)
			err_manager();
		else if (pid == 0)
			exec(mini, tk);
		waitpid(-1, &mini->status, 0);
	}
}
