/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:46:04 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/09 11:27:22 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	old_pwd(t_shell *mini, t_token *list)
{
	int i;

	i = -1;
	while (mini->env[++i])
	{
		if (ft_strncmp(mini->env[i], "OLDPWD", 6) == 0)
			list->s = var_content(mini, mini->env[i]);
	}
}

void	change_parent_folder(t_shell *mini, t_token *list)
{
	int		len;
	char	*str;

	len = ft_strlen(path);
	while (path[len] != '/' && len > 0)
		len--;
	if (path[0] == '/' && len == 0)	
	{
		mini->rtn = 2;
		return (0);
	}
	else
	{
	}
}

static int	check_valid_path(t_shell *mini, t_token *list, char *path)
{

}

int	parent_folder(t_shell *mini, t_token *list)
{
	char	*path;
	int		i;

	if (list->s == "..")
	{
		change_parent_folder(mini, list);
		return (1);
	}
	i = 2;
	path = getcwd(NULL, 0);
	while (list->s[i])
	{
		if (list->s[i] == '/')
		{
			if (!check_parent_folder(mini, list, path))
			{
				mini->rtn = 1;
				return (0);
			}

		}
		else
			return (0);
	}
}