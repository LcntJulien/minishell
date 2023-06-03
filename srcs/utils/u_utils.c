/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:54 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/03 11:12:04 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	oldpwd_status(t_shell *mini, int i, int flag)
{
	if (flag == 1)
		mini->env[i] = NULL;
	else
	{
		mini->env[i] = "OLPWD";
		mini->env[++i] = NULL;
	}
}

static int	check_oldpwd(char **env)
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

void	copy_env(t_shell *mini, char **env)
{
	int		i;
	int		flag;
	char	*var;

	i = -1;
	if (!env)
		ft_exit(mini, 0);
	flag = check_oldpwd(env); 
	if (flag == 1)
		mini->env = ft_calloc((i + 2), sizeof(char *));
	else
		mini->env = ft_calloc((i + 3), sizeof(char *));
	if (!mini->env)
		ft_exit(mini, 0);
	i = -1;
	while (env[++i])
	{
		var = ft_strdup(env[i]);
		mini->env[i] = var;
	}
	oldpwd_status(mini, i, flag);
}

char	*var_name(char *str)
{
	int		i;
	int		j;
	char	*s;
	
	i = 0;
	j = 0;
	if (*str)
	{
		while (str[i] && str[i] != '=')
			i++;
		s = malloc(sizeof(char) * (i + 1));
		if (!s)
			return (0);
		while(str[j] && j <= i)
		{
			s[j] = str[j]; 
			j++;
		}
		s[j] = '\0';
		return (s);
	}
	return (0);
}

char	*var_content(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*s;
	
	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (str[i] && str[i] != '=')
		i++;
	i++;
	if (i == len)
		return (0);
	s = malloc(sizeof(char) * (len - i + 1));
	if (!s)
		return (0);
	while(str[i] && i < len)
	{
		s[j] = str[i++]; 
		j++;
	}
	s[j] = '\0';
	return (s);
}
