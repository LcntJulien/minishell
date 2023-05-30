/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:54 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/30 10:02:23 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	oldpwd_status(t_shell *mini, int i, int flag)
{
	if (flag == 1)
		mini->env[i] = "\0";
	else
	{
		mini->env[i] = "OLPWD";
		mini->env[++i] = "\0";
	}
}

void	copy_env(t_shell *mini, char **env)
{
	int		i;
	int		flag;
	char	*var;

	i = -1;
	flag = 0;
	if (!env)
		ft_exit(mini, 0);
	while (env[++i])
	{
		if (!ft_strncmp(env[i],"OLDPWD", 6))
			flag = 1;	
	}
	if (flag == 1)
		mini->env = calloc((i + 2), sizeof(char *));
	else
		mini->env = calloc((i + 3), sizeof(char *));
	i = -1;
	while (env[++i])
	{
		var = ft_strdup(env[i]);
		mini->env[i] = var;
	}
	oldpwd_status(mini, i, flag);
}
