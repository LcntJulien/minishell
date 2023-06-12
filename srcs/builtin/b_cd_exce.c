/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_exce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 08:16:28 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/12 16:41:12 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	modify_pwd_and_tmp(t_shell *mini, char *tmp)
{
	int	i;

	i = -1;
	if (existing_var(mini, "PWD"))
	{
		while (mini->env[++i])
		{
			if (ft_strncmp(mini->env[i], "PWD", 3) == 0)
			{
				mini->env[i] = ft_strjoin("PWD=", tmp);
				break ;
			}
			else
				i++;
		}
	}
	mini->rtn = 0;
}

void	modify_pwd(t_shell *mini, t_token *list)
{
	int	i;

	i = -1;
	if (existing_var(mini, "PWD"))
	{
		while (mini->env[++i])
		{
			if (ft_strncmp(mini->env[i], "PWD", 3) == 0)
			{
				mini->env[i] = ft_strjoin("PWD=", list->s);
				if (!mini->env[i])
					ft_exit_plus(mini, list, 0);
				break ;
			}
			else
				i++;
		}
	}
	mini->rtn = 0;
}

void	modify_oldpwd(t_shell *mini, char **tmp)
{
	int	i;

	i = -1;
	if (existing_var(mini, "OLDPWD"))
	{
		*tmp = return_var_content(mini, "OLDPWD=");
		while (mini->env[++i])
		{
			if (ft_strncmp(mini->env[i], "OLDPWD", 6) == 0)
			{
				mini->env[i] = ft_strjoin("OLDPWD=",
						return_var_content(mini, "PWD="));
				break ;
			}
		}
	}
}

static void	modify_env(t_shell *mini, t_token *list, char *tmp_path)
{
	char	*tmp;

	tmp = NULL;
	modify_oldpwd(mini, &tmp);
	if (list->s[0] == '-' && list->s[1] == 0)
		modify_pwd_and_tmp(mini, tmp);
	else
	{
		list->s = tmp_path;
		modify_pwd(mini, list);
	}
}

void	cd_dispatch(t_shell *mini, t_token *list, char *tmp_path)
{
	if (chdir(tmp_path) == -1)
	{
		mini->rtn = 1;
		printf("minishell: cd: `%s': No such file or directory\n", list->s);
		return ;
	}
	else if (check_valid_path(tmp_path) == -1)
	{
		mini->rtn = 1;
		printf("minishell: cd: `%s': Not a directory\n", list->s);
		return ;
	}
	else
	{
		tmp_path = getcwd(NULL, 0);
		if (!tmp_path)
			ft_exit_plus(mini, list, 0);
		modify_env(mini, list, tmp_path);
	}
}
