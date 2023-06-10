/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_exce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 08:16:28 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/10 14:26:50 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	modify_oldpwd(t_shell *mini, t_token *list)
{
	int	i;

	i = -1;
	while (mini->env[++i])
	{
		if (ft_strncmp(mini->env[i], "PWD", 3) == 0)
		{
			mini->env[i] = ft_strjoin("PWD=", list->s);
			break ;
		}
		else
			i++;
	}
	mini->rtn = 0;
}

void	modify_pwd(t_shell *mini, t_token *list)
{
	int	i;
	char *tmp;

	i = -1;
	while (mini->env[++i])
	{
		if (ft_strncmp(mini->env[i], "PWD", 3) == 0)
			tmp = var_content(mini, mini->env[i]);
	}
	i = -1;
	while (mini->env[++i])
	{
		if (ft_strncmp(mini->env[i], "OLDPWD", 6) == 0)
		{
			mini->env[i] = ft_strjoin("OLDPWD=", tmp);
			break ;
		}
	}
	modify_oldpwd(mini, list);
}

int	check_valid_path(char *str)
{
	struct stat	buf;

	return (stat(str, &buf)); 
}

void	cd_dispatch(t_shell *mini, t_token *list, char *tmp_path)
{
	if (chdir(tmp_path) == -1)
	{
		mini->rtn = 1;
		printf("minishell: cd: `%s': No such file or directory\n", list->s);
	}
	else if (check_valid_path(tmp_path))
	{
		mini->rtn = 1;
		printf("minishell: cd: `%s': Not a directory\n", list->s);
	}
	else
	{
		list->s = tmp_path;
		modify_pwd(mini, list);
	}
}
