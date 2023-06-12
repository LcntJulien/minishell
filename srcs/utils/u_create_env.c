/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_create_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:54 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/12 15:39:26 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	oldpwd_status(t_shell *mini, int i, int flag)
{
	if (flag == 0)
		mini->env[i] = "OLPWD";
}

static int	check_oldpwd(char **env)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "OLDPWD", 6) == 0)
			flag = 1;
	}
	return (flag);
}

void	copy_env(t_shell *mini, char **env)
{
	int		i;
	int		flag;
	int		lines;

	if (!env)
		ft_exit(mini, 0);
	flag = check_oldpwd(env);
	lines = tab_lines(env);
	if (flag == 1)
		mini->env = ft_calloc((lines + 1), sizeof(char *));
	else
		mini->env = ft_calloc((lines + 2), sizeof(char *));
	if (!mini->env)
		ft_exit(mini, 0);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "_=", 2))
			mini->env[i] = "_=env";
		else
			mini->env[i] = env[i];
		if (!mini->env[i])
			ft_exit(mini, 0);
	}
	oldpwd_status(mini, i, flag);
}
