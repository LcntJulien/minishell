/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:28:35 by jlecorne          #+#    #+#             */
/*   Updated: 2023/06/15 18:40:27 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 - connaitre nb cmd -> parcourir liste chercher pipe
 - ouvrir scopes pour execution
	-> dup stdout/stdin/autre & fork pid pour attente d'exec
 - determiner process -> builtin/execve
 - boucler sur nb cmd -> set mini->token sur prochaine cmd/decla...
*/

void	child(t_shell *mini, t_token *tk, int i)
{
	if ()
}

void	minipipe(t_shell *mini, t_token *tk, int cmd)
{
	int	i;

	i = 0;
	mini->tab = malloc(sizeof(int **) * cmd);
	if (!mini->tab)
		err_manager();
	mini->pid = malloc(sizeof(pid_t) * cmd);
	if (!mini->pid)
		err_manager();
	while (i <= cmd)
	{
		if (pipe(mini->tab[i]) < 0)
			err_manager();
		i++;
	}
	i = 0;
	while (i <= cmd)
	{
		mini->pid[i] = fork();
		if (mini->pid[i] < 0)
			err_manager();
		child(mini, tk, i);
		next_cmd();
		i++;
	}
	i = 0;
	close_pipes();
	while (i++ < cmd)
		waitpid(-1, mini->status, 0);
	free_all();
}

int	nb_cmd(t_shell *mini)
{
	t_token	*tk;
	int		r;

	tk = mini->token;
	r = 0;
	while (tk)
	{
		if (tk->type == PIPE)
			r++;
		tk = tk->next;
	}
	return (r + 1);
}

void	minishell(t_shell *mini)
{
	t_token	*tk;
	int		cmd;

	tk = mini->token;
	cmd = nb_cmd(mini);
	if (cmd > 1)
		minipipe(mini, tk, cmd);
	else
	{
		if (tk->type == DECLAVAR)
			return ;
		else if (tk->type == INPUT)
			redir();
	}
}
