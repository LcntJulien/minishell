/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:31:16 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/27 14:35:35 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*folder(t_shell *mini, t_token *list, int c)
{
	if (c == 0)
	{
		c = existing_var(mini, "OLDPWD");
		if (c != -1 && ft_strncmp("OLDPWD=", mini->env[c], 7) == 0)
			return (var_content(mini, mini->env[existing_var(mini,
							"OLDPWD")]));
		else
			return (ft_strdup("OLDPWD"));
	}
	else if (c == 1)
	{
		if (list->s[1] && list->s[1] == '/')
			return (ft_strjoin(ft_strjoin(mini->home, "/"), list->s));
		else if (!list->s[1])
			return (ft_strdup(mini->home));
		else
			return (ft_strjoin(mini->home, list->s));
	}
	else
			return (ft_strdup(list->s));
}

static char	*check_str_cd(t_shell *mini, t_token *list)
{
	char	*tmp_path;

	if (ft_strncmp(list->s, "-", 1) == 0 && list->s[1] == 0)
		tmp_path = folder(mini, list, 0);
	else if (ft_strncmp(list->s, "~", 1) == 0)
		tmp_path = folder(mini, list, 1);
	else
		tmp_path = folder(mini, list, 2);
	if (!tmp_path)
		ft_exit_plus(mini, list, 0);
	return (tmp_path);
}

static int	args_before_cd(t_shell *mini, t_token *list)
{
	if (!list->next)
	{
		if (existing_var(mini, "HOME=") == -1)
		{
			mini->rtn = 1;
			ft_putstr_fd("minishell: cd: HOME not set\n", mini->out);
		}
		else
		{
			free(list->s);
			list->s = NULL;
			list->s = return_var_content(mini, "HOME=");
			check_var_status(mini, list, list->s);
		}
		return (0);
	}
	else
		return (1);
}

int	valid_path(t_shell *mini, char *tmp_path)
{
	if (chdir(tmp_path) == -1)
	{
		mini->rtn = 1;
		perror(ft_strjoin("minishell: cd: ", tmp_path));
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
			ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: cd: ", tmp_path),
					" not set\n"), mini->out);
			free(tmp_path);
			tmp_path = NULL;
			return ;
		}
		check_var_status(mini, list, tmp_path);
		free(tmp_path);
		tmp_path = NULL;
	}
	else
		check_var_status(mini, list, list->s);
}
