/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:54 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/29 07:55:33 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	copy_env(t_shell *mini, char **env)
{
	int		i;
	char	*var;

	i = 0;
	if (!env)
		ft_exit(mini, 0);
	while (env[i])
		i++;
	mini->env = calloc((i + 2), sizeof(char *));
	i = -1;
	while (env[++i])
	{
		var = ft_strdup(env[i]);
		mini->env[i] = var;
	}
	mini->env[i] = "OLPWD";
	mini->env[++i] = "\0";
}
