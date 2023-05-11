/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:31:15 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/11 14:48:00 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_shell *mini, char **envp)
{
	char	*var;
	int	 	i;
	int		j;

	i = 0;
	j = 0;
	if (!envp)
		exit (0);	
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	mini->envi = calloc(sizeof(char *), (i + 1));
	while (envp[j] <= envp[i])
	{
		var = ft_strdup(envp[j]);
		j++;
		free(var);
	}		
}