/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_create_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:54 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/05 17:47:46 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	oldpwd_status(t_shell *mini, int i, int flag)
{
	if (flag == 0)
		mini->env[i] = ft_strdup("OLDPWD");
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

static int	get_shlvl(char *str)
{
	int		i;
	int		start;
	int		end;	
	char	*shlvl;

	i = 0;
	start = 0;
	while (str[start] && str[start] != '=')
		start++;
	end = ft_strlen(str); 	
	shlvl = ft_calloc(sizeof(char), (end - start));
	if (!shlvl)
		return (-1);
	while (str[++start])
		shlvl[i++] = str[start];
	return (ft_atoi(shlvl));	
}

static void	copy_env(t_shell *mini, char **env, int flag)
{
	int	i;
	int	shlvl;

	i = -1;
	shlvl = 0;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
			mini->env[i] = ft_substr(env[i], 0, 6);
		if (!ft_strncmp(env[i], "SHLVL=", 5))
		{
			shlvl = get_shlvl(env[i]) + 1;
			if (shlvl == -1 || shlvl == 0)
				ft_exit(mini, 0);
			mini->env[i] = ft_strjoin("SHLVL=", ft_itoa(shlvl));
		}
		else if (!ft_strncmp(env[i], "_=", 2))
			mini->env[i] = ft_strjoin("_=",
					ft_strjoin(getcwd(NULL, 0), "/minishell"));
		else
			mini->env[i] = ft_strdup(env[i]);
		if (!mini->env[i])
			ft_exit_plus(mini, mini->token, 0);
	}
	oldpwd_status(mini, i, flag);
}

void	alloc_env(t_shell *mini, char **env)
{
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
	copy_env(mini, env, flag);
}
