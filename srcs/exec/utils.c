/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:38:41 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/28 15:49:35 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**args_alloc(t_token *tk)
{
	t_token	*cp;
	char	**args;
	int		i;

	cp = tk;
	args = NULL;
	i = 0;
	while (cp && cp->type != PIPE)
	{
		i++;
		cp = cp->next;
	}
	args = malloc(sizeof(char *) * i + 1);
	if (!args)
		return (NULL);
	return (args);
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

void	pipe_alloc(t_shell *mini)
{
	int	i;

	i = 0;
	mini->tab = malloc(sizeof(int *) * mini->ncmd);
	while (i < mini->ncmd)
		mini->tab[i++] = malloc(sizeof(int) * 2);
	mini->pid = malloc(sizeof(pid_t) * mini->ncmd);
}

void	get_paths(t_shell *mini)
{
	int		i;
	char	*paths;

	i = 0;
	paths = NULL;
	while (mini->env[i])
	{
		if (!ft_strncmp("PATH=", mini->env[i], 5))
		{
			paths = ft_substr(mini->env[i], 5, 200);
			break ;
		}
		i++;
	}
	mini->paths = custom_split(paths, ':', 1);
	free(paths);
}

void	get_args(t_shell *mini, t_token *tk)
{
	t_token	*cp;
	int		i;

	cp = tk;
	i = 0;
	while (cp->prev && cp->prev->type != PIPE)
		cp = cp->prev;
	if (is_redir(cp, 0))
		args_redir(mini, cp);
	else
	{
		mini->args = args_alloc(cp);
		while (cp && cp->type != PIPE)
		{
			mini->args[i++] = cp->s;
			cp = cp->next;
		}
		mini->args[i] = NULL;
	}
}

char	*get_cmd(t_shell *mini)
{
	int		i;
	char	*pathcmd;

	i = -1;
	pathcmd = NULL;
	while (mini->paths[++i])
	{
		pathcmd = ft_strjoin(mini->paths[i], mini->args[0]);
		if (access(pathcmd, X_OK) == 0)
			return (pathcmd);
		free(pathcmd);
		pathcmd = NULL;
	}
	if (access(mini->args[0], X_OK) == 0)
		return (mini->args[0]);
	return (NULL);
}
