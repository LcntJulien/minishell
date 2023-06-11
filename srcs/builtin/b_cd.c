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

static char	*another_folder(t_shell *mini, t_token *list)
{
	char	*folder_name;
	int		i;
	int		len;

	if (list->s[0] != '/')	
	{
		i = 0;
		len = ft_strlen(list->s);
		while (list->s[i] && list->s[i] != '/')
			i++;
		folder_name = calloc(sizeof(char *), (len - i + 1));
		if (!folder_name)
			ft_exit_plus(mini, list, 0);
		while (i < len)	
		{
			folder_name[i] = list->s[i];
			i++;
		}
		return(ft_strjoin(ft_strjoin(getcwd(NULL, 0), "/"), folder_name));
	}
	else
		return (list->s);
}

static char *cd_check_args(t_shell *mini, t_token *list)
{
	char *tmp_path;

	if (ft_strncmp(list->s, "-", 1) == 0)
		tmp_path = old_pwd(mini, list);
	if (ft_strncmp(list->s, "~", 1) == 0)
		tmp_path = home_path(mini, list);
	else if (list->s[0] == '/' && !list->s[1])	
		tmp_path = ft_strdup("/");
	else
		tmp_path = another_folder(mini, list);
	if (!tmp_path)
		return (0);
	return (tmp_path);
}

static void	without_arg(t_shell *mini, t_token *list)
{
	if (!existing_var(mini, "HOME="))
	{
		mini->rtn = 1;
		printf("minishell: cd: HOME not set\n");
		return ;
	}
	else
	{
		list->s = return_var_content(mini, "HOME=");
		modify_pwd(mini, list);
		return ;
	}
}

void	b_cd(t_shell *mini, t_token *list)
{
	char *tmp_path;

	list = mini->token;
	if (!list->next)
	{
		without_arg(mini, list);
		return ;
	}
	list = list->next;
	tmp_path = cd_check_args(mini, list);
	if (ft_strncmp(tmp_path, "HOME", 4) == 0 || ft_strncmp(tmp_path, "OLDPWD", 6) == 0)
	{
		mini->rtn = 1;
		printf("minishell: cd: %s not set\n", tmp_path);
		return ;
	}
	cd_dispatch(mini, list, tmp_path);
}
