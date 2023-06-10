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

int	check_valid_path(char *str)
{
	struct stat	buf;

	return (stat(str, &buf)); 
}

static void	cd_dispatch(t_shell *mini, t_token *list)
{
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

void	search_folder_name(t_token *list, int i)
{


}

static char	*another_folder(t_shell *mini, t_token *list)
{
	char	*str;
	int		i;

	i = 0;
	if (list->s[0] == '/' && !list->s[1])	
		return (ft_strdup("/"));
	else if (list->s[0] != '/')	
	{
		i++;
		while (list->s[i] && list->s[i] != '/')
			i++;
		search_folder_name(list, i);
		

			str = getcwd(NULL, 0);
			return(ft_strjoin(str, list->s));
		}
		else
			return (ft_strdup("/"));

	}
	else
	{

	}
}

static char *cd_check_args(t_shell *mini, t_token *list)
{
	char *tmp_path;

	if (ft_strncmp(list->s, "-", 1) == 0)
		tmp_path = old_pwd(mini, list);
	else if (ft_strncmp(list->s, "..", 2) == 0)
		tmp_path = parent_folder(mini, list);
	else
		tmp_path = another_folder(mini, list);
	if (!tmp_path)
		return (0);
	return (tmp_path);
}

void	b_cd(t_shell *mini, t_token *list)
{
	char *logname;
	char *tmp_path;

	list = mini->token;
	if (!list->next)
	{
		logname = var_content(mini, "LOGNAME");
		list->s = ft_strjoin("/home/", logname);
		modify_pwd(mini, list);
		return ;
	}
	list = list->next;
	tmp_path = cd_check_args(mini, list);
	if (!tmp_path)
		ft_exit_plus(mini, list, 0);
	cd_dispatch(mini, list);
}
