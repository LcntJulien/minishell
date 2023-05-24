/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:54 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/24 14:54:51 by jmathieu         ###   ########.fr       */
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

void	find_pwd(t_shell *mini)
{
	int	i;

	i = -1;
	while (mini->env[++i])
	{
		if (!ft_strncmp(mini->env[i], "PWD=", 4))
			mini->pwd = ft_substr(mini->env[i], 4,
					ft_strlen(mini->env[i]) - 4);
		if (!ft_strncmp(mini->env[i], "OLDPWD=", 7))
			mini->oldpwd = ft_substr(mini->env[i], 7,
					ft_strlen(mini->env[i]) - 7);
	}
}

char	*format_string(char *str)
{
	int		i;
	char	*newstr;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			printf("test");
		}
	}
	return (newstr);
}
