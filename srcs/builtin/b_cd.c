/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:06 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/12 19:59:28 by jmathieu         ###   ########.fr       */
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
		return (ft_strjoin(ft_strjoin(getcwd(NULL, 0), "/"), folder_name));
	}
	else
		return (list->s);
}

static char	*check_str_cd(t_shell *mini, t_token *list)
{
	char	*tmp_path;

	if (ft_strncmp(list->s, "-", 1) == 0 && list->s[1] == 0)
		tmp_path = old_pwd(mini);
	else if (ft_strncmp(list->s, "~", 1) == 0)
		tmp_path = home_path(mini, list);
	else
		tmp_path = another_folder(mini, list);
	if (!tmp_path)
		ft_exit_plus(mini, list, 0);
	return (tmp_path);
}

static void	without_arg(t_shell *mini, t_token *list)
{
	if (existing_var(mini, "HOME=") != -1)
	{
		mini->rtn = 1;
		printf("minishell: cd: HOME not set\n");
		return ;
	}
	else
	{
		free(list->s);
		list->s = return_var_content(mini, "HOME=");
		check_var_status(mini, list, list->s);
		return ;
	}
}

static int	args_before_cd(t_shell *mini, t_token *list)
{
	if (!list->next)
	{
		without_arg(mini, list);
		mini->rtn = 1;
		return (0);
	}
	else if (list->next && (list->next->type == 1 || list->next->type == 2
			|| list->next->type == 3) && list->next->next
		&& (list->next->next->type == 1 || list->next->next->type == 2
			|| list->next->next->type == 3))
	{
		printf("minishell: cd: Too many arguments\n");
		mini->rtn = 1;
		return (0);
	}
	else
		return (1);
}

void	b_cd(t_shell *mini, t_token *list)
{
	char	*tmp_path;

	if (!args_before_cd(mini, list))
		return ;
	list = list->next;
	if (ft_strncmp(list->s, "..", 2) != 0)
	{	
		tmp_path = check_str_cd(mini, list);
		if (ft_strncmp(tmp_path, "HOME", 4) == 0
			|| ft_strncmp(tmp_path, "OLDPWD", 6) == 0)
		{
			mini->rtn = 1;
			printf("minishell: cd: %s not set\n", tmp_path);
			return ;
		}
		check_var_status(mini, list, tmp_path);
	}
	else
		check_var_status(mini, list, list->s);
}
