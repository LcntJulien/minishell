/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:07:59 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/11 17:52:53 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

void	ft_env(t_shell *mini, char **envp)
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
