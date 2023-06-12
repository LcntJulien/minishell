/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_exce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 08:16:28 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/12 20:10:41by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	modify_pwd_and_tmp(t_shell *mini, char *tmp)
{
	int	i;

	i = existing_var(mini, "PWD");
	if (i != -1)
	{
		free(mini->env[i]);
		mini->env[i] = ft_strjoin("PWD=", tmp);
		printf("%s\n", mini->env[i]);
	}
	mini->rtn = 0;
}

void	modify_pwd(t_shell *mini, t_token *list)
{
	int	i;

	i = existing_var(mini, "PWD");
	if (i != -1)
	{
		free(mini->env[i]);
		mini->env[i] = ft_strjoin("PWD=", list->s);
	}
	mini->rtn = 0;
}

void	modify_oldpwd(t_shell *mini, char **tmp)
{
	int	i;

	i = existing_var(mini, "PWD");
	if (i != -1)
	{
		*tmp = return_var_content(mini, "OLDPWD=");
		mini->env[i] = ft_strjoin("OLDPWD=",
				return_var_content(mini, "PWD="));
	}
}

static void	modify_env(t_shell *mini, t_token *list, char *tmp_path,
	char *tmp_pwd)
{
	char	*tmp;
	int		c;

	tmp = NULL;
	c = existing_var(mini, "OLDPWD");
	if (c != -1)
	{
		modify_oldpwd(mini, &tmp);
		if (list->s[0] == '-' && list->s[1] == 0)
			modify_pwd_and_tmp(mini, tmp);
		tmp_pwd = NULL;
	}
	else
	{
		list->s = tmp_path;
		modify_pwd(mini, list);
	}
}

void	check_var_status(t_shell *mini, t_token *list, char *tmp_path)
{
	char	*tmp_pwd;

	tmp_pwd = NULL;
	if (existing_var(mini, "PWD") == -1)
	{
		tmp_pwd = getcwd(NULL, 0);
		if (!valid_path(mini, list, tmp_path))
		{
			free(tmp_pwd);
			free(tmp_path);
			return ;
		}
	}
	else
	{
		if (!valid_path(mini, list, tmp_path))
		{
			free(tmp_path);
			return ;
		}
	}
	tmp_path = getcwd(NULL, 0);
	modify_env(mini, list, tmp_path, tmp_pwd);
	free_cd(tmp_path, tmp_pwd);
}
