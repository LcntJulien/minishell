/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:28:35 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/04 16:05:17 by jlecorne         ###   ########.fr       */
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
		execve(mini->cmd, mini->args, mini->env);
		exit(EXIT_FAILURE);
	}
}

void	child(t_shell *mini, t_token *tk, int tab[][2], int i)
{
	// if (is_redir(tk) == 0)
	// {
	if (i == 0)
	{
		dup2(tab[i][0], STDIN_FILENO);
		dup2(tab[i + 1][1], STDOUT_FILENO);
	}
	else if (i == mini->ncmd - 1)
		dup2(tab[i][0], STDIN_FILENO);
	else
	{
		dup2(tab[i][0], STDIN_FILENO);
		dup2(tab[i + 1][1], STDOUT_FILENO);
	}
	close_child(mini, tab, i);
	// }
	exec(mini, tk);
}

void	minipipe(t_shell *mini, t_token *tk)
{
	int		i;
	int		tab[mini->ncmd][2];
	pid_t	pid[mini->ncmd];

	i = 0;
	while (i < mini->ncmd)
		if (pipe(tab[i++]) < 0)
			err_manager();
	i = 0;
	while (i < mini->ncmd)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			err_manager();
		if (pid[i] == 0)
			child(mini, tk, tab, i);
		tk = next_cmd(tk);
		i++;
	}
	i = 0;
	close_pipes(mini, tab);
	while (i < mini->ncmd)
		waitpid(pid[i++], &mini->rtn, 0);
	// free_cpa(mini);
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
		pid = fork();
		if (pid < 0)
			err_manager();
		else if (pid == 0)
			exec(mini, tk);
		waitpid(-1, &mini->rtn, 0);
	}
	// free_cpa(mini);
}
