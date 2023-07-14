/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:28:35 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/14 17:43:06 by jmathieu         ###   ########.fr       */
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
	if (tk && tk->type == BUILTIN)
	{
		b_process(mini);
		exit(EXIT_SUCCESS);
	}
	else
	{
		mini->args = get_args(tk);
		mini->cmd = get_cmd(mini);
		if (!mini->cmd)
			err_manager();
		execve(mini->cmd, mini->args, mini->env);
		exit(EXIT_SUCCESS);
	}
}

void	child(t_shell *mini, t_token *tk, int i)
{
	// if (is_redir(tk) == 0)
	// {
	if (i == 0)
		dup2(mini->tab[i + 1][1], STDOUT_FILENO);
	else if (i == mini->ncmd - 1)
		dup2(mini->tab[i][0], STDIN_FILENO);
	else
	{
		dup2(mini->tab[i][0], STDIN_FILENO);
		dup2(mini->tab[i + 1][1], STDOUT_FILENO);
	}
	// }
	close_pipes(mini, i, 1);
	exec(mini, tk);
}

void	minipipe(t_shell *mini, t_token *tk)
{
	int	i;

	i = 0;
	pipe_alloc(mini);
	while (i < mini->ncmd)
		if (pipe(mini->tab[i++]) < 0)
			err_manager();
	i = 0;
	while (i < mini->ncmd)
	{
		mini->pid[i] = fork();
		if (mini->pid[i] < 0)
			err_manager();
		if (mini->pid[i] == 0)
			child(mini, tk, i);
		tk = next_cmd(tk);
		i++;
	}
	i = 0;
	close_pipes(mini, i, 0);
	while (i < mini->ncmd)
		waitpid(mini->pid[i++], &mini->rtn, 0);
	mini_free(mini);
}

void	minishell(t_shell *mini)
{
	t_token	*tk;
	pid_t	pid;

	tk = mini->token;
	mini->ncmd = nb_cmd(mini);
	get_paths(mini);
	if (mini->ncmd > 1)
		minipipe(mini, tk);
	else
	{
		if (tk && tk->type == BUILTIN)
			b_process(mini);
		else
		{
			pid = fork();
			if (pid < 0)
				err_manager();
			else if (pid == 0)
				exec(mini, tk);
			waitpid(0, &mini->rtn, 0);
		}
	}
}
