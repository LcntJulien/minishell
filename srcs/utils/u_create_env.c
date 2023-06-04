/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_create_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:54 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/04 10:03:02 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	oldpwd_status(t_shell *mini, int i, int flag, int c)
{
	if (c == 0)
	{
		if (flag == 1)
			mini->env[i] = NULL;
		else
		{
			mini->env[i] = "OLPWD";
			mini->env[++i] = NULL;
		}
	}
	else
	{
		if (flag == 1)
			return ;
		else
			mini->env[i] = "OLPWD";
	}
}

int	check_oldpwd(char **env)
{
	int i;
	int	flag;

	i = -1;
	flag = 0;
	while (env[++i])
	{
		if (!ft_strncmp(env[i],"OLDPWD", 6))
			flag = 1;	
	}
	return (flag);
}

int	tab_lines(char **tab)
{
	int i;
	int	lines;

	i = 0;
	lines = 0;
	while (tab[i])
	{
		if (ft_strchr(tab[i], '=') != NULL)
			lines++;
		i++;
	}
	return (lines);
}

void	copy_env(t_shell *mini, char **env)
{
	int		i;
	int		flag;
	int		lines;
	char	*var;

	i = -1;
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
	while (env[++i])
	{
		var = ft_strdup(env[i]);
		mini->env[i] = var;
	}
	oldpwd_status(mini, i, flag, 0);
}
