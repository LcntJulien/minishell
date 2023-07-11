/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_env_excepts.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:25:39 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/11 18:36:47 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_last(t_shell *mini, char **env, int i)
{
	char	*fstr;
	char	*lstr;
	
	fstr = NULL;
	lstr = NULL;
	if (!ft_strncmp(env[i], "_=", 2))
	{
		fstr = getcwd(NULL, 0);
		lstr = ft_strjoin(fstr, "/minishell");
		mini->env[i] = ft_strjoin("_=", lstr);
		free_str(fstr);
		free_str(lstr);
		return (1);
	}
	return (0);
}

int	check_shlvl(t_shell *mini, char **env, int i)
{
	int		shlvl;
	char	*str;
	
	shlvl = 0;
	str = NULL;
	if (!ft_strncmp(env[i], "SHLVL=", 5))
	{
		shlvl = get_shlvl(env[i]) + 1;
		if (shlvl == -1 || shlvl == 0)
			ft_exit_plus(mini, "Fail to initiate bash level\n", 1);
		str = ft_itoa(shlvl);
		mini->env[i] = ft_strjoin("SHLVL=", str);
		free_str(str);
		return (1);
	}
	return (0);
}

int	check_oldpwd(t_shell *mini, char **env, int i)
{
	if (!ft_strncmp(env[i], "OLDPWD=", 7))
	{
		mini->env[i] = ft_substr(env[i], 0, 6);
		return (1);
	}
	return (0);
}