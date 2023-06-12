/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:46:04 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/12 18:53:03 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_valid_path(char *str)
{
	struct stat	buf;

	return (stat(str, &buf));
}

static char	*substract_folder_name(t_shell *mini, t_token *list)
{
	int		i;
	int		len;
	char	*folder_name;

	i = 0;
	len = ft_strlen(list->s);
	while (list->s[i] && list->s[i] == '/')
		i++;
	folder_name = ft_calloc(sizeof(char *), (len - i + 1));
	if (!folder_name)
		ft_exit_plus(mini, mini->token, 0);
	while (i < len)
	{
		folder_name[i] = list->s[i];
		i++;
	}
	return (folder_name);
}

char	*home_path(t_shell *mini, t_token *list)
{
	if (list->s[1] && list->s[1] == '/')
		return (ft_strjoin(ft_strjoin(mini->home, "/"),
				substract_folder_name(mini, list)));
	return (mini->home);
}

char	*old_pwd(t_shell *mini)
{
	int	i;

	i = existing_var(mini, "OLDPWD");
	if (i != -1)
		return (var_content(mini, mini->env[i]));
	else
		return ("OLDPWD");
}

int	valid_path(t_shell *mini, t_token *list, char *tmp_path)
{
	if (chdir(tmp_path) == -1)
	{
		mini->rtn = 1;
		printf("minishell: cd: `%s': No such file or directory\n", list->s);
		return (0);
	}
	else if (check_valid_path(tmp_path) == -1)
	{
		mini->rtn = 1;
		printf("minishell: cd: `%s': Not a directory\n", list->s);
		return (0);
	}
	/* gerer les acces et droits */
	else
		return (1);
}
