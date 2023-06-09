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

static int	cd_check_args(t_shell *mini, t_token *list)
{
	if (list->s == "-")
		old_pwd(mini, list);
	else if (ft_strncmp(list->s, "..", 2))
		parent_folder(mini, list);
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
	cd_check_args(mini, list);
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
