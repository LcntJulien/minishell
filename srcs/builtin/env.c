/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:07:59 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/13 12:04:23 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

void	copy_env(t_shell *mini, char **envp)
{
	int		i;
	char	*var;
	
	i = 0;
	if (!envp)
		exit (0);	
	while (envp[i])
		i++;
	mini->env = calloc((i + 1), sizeof(char *));
	i = -1;
	while (envp[++i])
	{
		var = ft_strdup(envp[i]);
		mini->env[i] = var;
	}
}

// Attention, le cas de l'argument 0 est faux, il faut prendre en compte
// les autres arguments, tels que les redirections, etc...
// Le renvoie et la sortie doit se faire aussi en fonction des arguments
void	env(t_shell *mini, char **tab)
{
	int	i;

	if (tab[0])
	{
		mini->rtn = 1;
		return ;
	}	
	else
	{
		i = -1;
		while (mini->env[++i])
			printf("%s\n", mini->env[i]);		
	}	
}
