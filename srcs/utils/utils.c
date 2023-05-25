/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:54 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/25 12:30:50 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	copy_env(t_shell *mini, char **env)
{
	int		i;
	char	*var;

	i = 0;
	if (!env)
		exit (0);
	while (env[i])
		i++;
	mini->env = calloc((i + 1), sizeof(char *));
	i = -1;
	while (env[++i])
	{
		var = ft_strdup(env[i]);
		mini->env[i] = var;
	}
	mini->env[i] = "\0";
}
