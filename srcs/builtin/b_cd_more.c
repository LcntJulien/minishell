/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:46:04 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/10 01:54:15 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*old_pwd(t_shell *mini, t_token *list)
{
	int		i;
	char	*tmp_path;

	i = -1;
	tmp_path = 0;
	while (mini->env[++i])
	{
		if (ft_strncmp(mini->env[i], "OLDPWD", 6) == 0)
			tmp_path = var_content(mini, mini->env[i]);
	}
}

static char *previous_folder(t_shell *mini, t_token *list, char *path)
{
	int		len;
	int		i;
	char	*str;

	len = ft_strlen(path);
	if (len == 1)	
	{
		str = calloc(sizeof(char *), (len + 1));
		if (!str)
			ft_exit_plus(mini, list, 0);
		str[0] = '/';
	}
	else
	{
		while (path[len] != '/' && len > 0)
			len--;
		str = calloc(sizeof(char *), (len + 1));
		if (!str)
			ft_exit_plus(mini, list, 0);
		i = -1;
		while (++i < len)
			str[i] = path[i];
	}
	return (str);
}

static int	test_redir(char *redir)
{
	if (chdir(redir) == -1)
		return (0);
	else if (check_valid_path(redir) == -1)
		return (0);
	else
		return (1);
}	

static char	*next_folder(char *path, int *i, t_shell *mini, t_token *list)
{
	char	*str;
	int		j;
	int		k;

	while (path[*i] && path[*i] != '/')
	{
		(*i)++;
		j++;
	}
	str = calloc(sizeof(char *), (j + 1));
	if (!str)
		ft_exit_plus(mini, list, 0);
	k = -1;
	while (++k < j)
		str[k] = path[k];
	return (str);
}

char	*parent_folder(t_shell *mini, t_token *list)
{
	char	*path;
	char	*redir;
	int		i;

	path = getcwd(NULL, 0);
	i = 0;
	redir = calloc(sizeof(char *), 1);
	if (!redir)
		ft_exit_plus(mini, list, 0);
	while (list->s[i])
	{
		while (list->s[i] != '/' && list->s[i])
			i++;
		if (list->s[i - 2] == '.' && list->s[i - 1] == '.')
		{
			redir = previous_folder(mini, list, path);
			if (!test_redir(redir))
				return (NULL);
		}
		else
			redir = ft_strjoin(redir, next_folder(list->s, &i, mini, list));
	}
	return (redir);
}
