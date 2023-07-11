/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_create_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:54 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/11 14:20:57 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_oldpwd(char **env)
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

int	get_shlvl(char *str)
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
	i = ft_atoi(shlvl);
	free(shlvl);
	shlvl = NULL;
	return (i);	
}

static int	env_exceptions(t_shell *mini, char **env, int i)
{
	// int		shlvl;
	// char	*str;
	
	// shlvl = 0;
	// str = NULL;
	if (check_oldpwd(mini, env, i))
		return (1);
	else if (check_shlvl(mini, env, i))	
		return (1);
	else if (check_last(mini, env, i))
		return (1);
	else
		return (0);
}

static void	copy_env(t_shell *mini, char **env, int flag)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!env_exceptions(mini, env, i))
			mini->env[i] = ft_strdup(env[i]);
		if (!mini->env[i])
			ft_exit_plus(mini, mini->token, 0);
	}
	if (flag == 0)
		mini->env[i] = ft_strdup("OLDPWD");
}

void	alloc_env(t_shell *mini, char **env)
{
	int		flag;
	int		lines;

	if (!env)
		ft_exit(mini, 0);
	flag = ft_oldpwd(env);
	lines = tab_lines(env);
	if (flag == 1)
		mini->env = ft_calloc((lines + 1), sizeof(char *));
	else
		mini->env = ft_calloc((lines + 2), sizeof(char *));
	if (!mini->env)
		ft_exit(mini, 0);
	copy_env(mini, env, flag);
}
