/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:06 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/07 19:55:48by jmathieu         ###   ########.fr       */
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
}

static void	modify_pwd(t_shell *mini, t_token *list)
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

static int	check_valid_path(char *str)
{
	struct stat	buf;

	return (stat(str, &buf)); 
}

static void	old_pwd(t_shell *mini, t_token *list)
{
	int i;

	i = -1;
	while (mini->env[++i])
	{
		if (ft_strncmp(mini->env[i], "OLDPWD", 6) == 0)
			list->s = var_content(mini, mini->env[i]);
	}
}

void	b_cd(t_shell *mini, t_token *list)
{
	list = mini->token;
	if (!list->next)
	{
		mini->rtn = 0;
		return ;
	}
	list = list->next;
	if (strncmp(list->s, "-", 1) == 0)
		old_pwd(mini, list);
	if (chdir(list->s) == -1)
	{
		mini->rtn = 1;
		printf("minishell: cd: `%s': No such file or directory\n", list->s);
	}
	else if (check_valid_path(list->s))
	{
		mini->rtn = 1;
		printf("minishell: cd: `%s': Not a directory\n", list->s);
	}
	else
		modify_pwd(mini, list);
}
