/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:28:35 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/13 16:27:57 by jlecorne         ###   ########.fr       */
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
		fprintf(stderr, "exec\n");
		execve(mini->cmd, mini->args, mini->env);
		exit(EXIT_FAILURE);
	}
}

void	redir_close(t_shell *mini, t_token *tk)
{
	fprintf(stderr, "close(mini->fd[1]);\n");
	close(mini->fd[1]);
	if (!is_hrdc(tk))
	{
		fprintf(stderr, "close(mini->fd[0]);\n");
		close(mini->fd[0]);
	}
	if (!is_redir(tk, 1))
	{
		fprintf(stderr, "close(mini->in);\n");
		close(mini->in);
	}
	if (!is_redir(tk, 2))
	{
		fprintf(stderr, "close(mini->out);\n");
		close(mini->out);
	}
}

void	child(t_shell *mini, t_token *tk, int i)
{
	fprintf(stderr, "child\n");
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

void	minipipe(t_shell *mini, t_token *tk)
{
	pid_t	pid;
	int		i;

	i = -1;
	g_sig = 300;
	pipe_alloc(mini);
	reset_std(mini);
	while (++i < mini->ncmd)
	{
		pid = fork();
		if (pid == -1)
			err_manager(mini, NULL, 2);
		else if (!pid)
		{
			child(mini, tk, i);
			exit(0);
		}
		// hrdc_close(mini, get_htab(mini, i), 0);
		// close_pipes(mini, tk, i, 0);
		waitpid(pid, &mini->rtn, 0);
		mini->rtn = WEXITSTATUS(mini->rtn);
		if (mini->rtn != 0)
			break ;
		// reset_std(mini);
		tk = next_cmd(tk);
	}
	// reset_std(mini);
	// hrdc_close(mini, get_htab(mini, i), 0);
	// close_pipes(mini, tk, i, 0);
}

// void	minipipe(t_shell *mini, t_token *tk)
// {
// 	int	i;

// 	i = 0;
// 	pipe_alloc(mini);
// 	g_sig = 300;
// 	if (hrdc_manager(mini))
// 		return ;
// 	i = -1;
// 	while (++i < mini->ncmd)
// 	{
// 		mini->pid[i] = fork();
// 		if (mini->pid[i] < 0)
// 			err_manager(mini, tk, 2);
// 		if (mini->pid[i] == 0)
// 			child(mini, tk, i);
// 		tk = next_cmd(tk);
// 	}
// 	hrdc_close(mini, get_htab(mini, i), 0);
// 	close_pipes(mini, i, 0);
// 	// while (++i < mini->ncmd)
// 	// 	waitpid(mini->pid[i], &mini->rtn, 0);
// 	// mini->rtn = WEXITSTATUS(mini->rtn);
// }

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
