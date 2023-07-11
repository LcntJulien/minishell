/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:31:16 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/11 14:17:52 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*check_str_cd(t_shell *mini, t_token *list)
{
	char	*tmp_path;

	if (ft_strncmp(list->s, "-", 1) == 0 && list->s[1] == 0)
		tmp_path = folder1(mini);
	else if (ft_strncmp(list->s, "~", 1) == 0)
		tmp_path = folder2(mini, list);
	else
		tmp_path = ft_strdup(list->s);
	return (tmp_path);
}

void	next_cd_step(t_shell *mini, t_token *list, char *cur_dir)
{
	char	*tmp_path;

	if (ft_strncmp(list->s, "..", 2) != 0)
	{	
		tmp_path = check_str_cd(mini, list);
		if (ft_strncmp(tmp_path, "HOME", 4) == 0
			|| ft_strncmp(tmp_path, "OLDPWD", 6) == 0)
		{
			mini->rtn = 1;
			ft_putstr_fd("minishell: cd: ", STDOUT_FILENO);
			ft_putstr_fd(tmp_path, STDOUT_FILENO);
			ft_putstr_fd(" not set\n", STDOUT_FILENO);
			free(tmp_path);
			tmp_path = NULL;
			return ;
		}
		check_var_status(mini, list, tmp_path, cur_dir);
		free(tmp_path);
		tmp_path = NULL;
	}
	else
		check_var_status(mini, list, list->s, cur_dir);
}

static int	args_before_cd(t_shell *mini, t_token *list, char *cur_dir)
{
	if (!list->next)
	{
		if (existing_var(mini, "HOME=") == -1)
		{
			mini->rtn = 1;
			ft_putstr_fd("minishell: cd: HOME not set\n", STDOUT_FILENO);
			return (1);
		}
		else
		{
			free(list->s);
			list->s = NULL;
			list->s = return_var_content(mini, "HOME=");
			check_var_status(mini, list, list->s, cur_dir);
			return (0);
		}
	}
	return (1);
}

void	b_cd(t_shell *mini, t_token *list)
{
	char	*cur_dir;

	cur_dir = getcwd(NULL, 0);
	if (!cur_dir)
	{
		ft_putstr_fd("No directory\n", STDOUT_FILENO);
		ft_exit_plus(mini);
		mini->rtn = -1;
		exit(mini->rtn);
	}
	if (!args_before_cd(mini, list, cur_dir))
		return ;
	list = list->next;
	next_cd_step(mini, list, cur_dir);
	free_str(cur_dir);
}
