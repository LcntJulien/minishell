/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:38:41 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/03 23:32:22 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	**get_args(t_token *tk)
{
	int		i;
	char	**args;
	t_token	*cpy;

	i = 0;
	cpy = tk;
	while (cpy && cpy->type != PIPE)
	{
		i++;
		cpy = cpy->next;
	}
	cpy = tk;
	args = malloc(sizeof(char *) * i + 1);
	if (!args)
		return (NULL);
	i = 0;
	while (cpy && cpy->type != PIPE)
	{
		args[i++] = cpy->s;
		cpy = cpy->next;
	}
	args[i] = NULL;
	return (args);
}

char	*get_cmd(t_shell *mini)
{
	int		i;
	char	*pathcmd;

	i = 0;
	while (mini->paths[i])
	{
		pathcmd = ft_strjoin(mini->paths[i], mini->args[0]);
		if (access(pathcmd, X_OK) == 0)
			return (pathcmd);
		// free(pathcmd);
		i++;
	}
	if (access(mini->args[0], 0) == 0)
		return (mini->args[0]);
	return (NULL);
}
