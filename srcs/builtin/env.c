/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:31:15 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/11 15:51:19 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_shell *mini, char **envp)
{
	int		i;
	int		j;
	char	*var;
	
	i = 0;
	j = 0;
	if (!envp)
		exit (0);	
	while (envp[i])
		i++;
	mini->env = calloc((i + 1), sizeof(char *));
	while (envp[j])
	{
		var = ft_strdup(envp[j]);
		mini->env[j] = var;
		j++;
	}
}