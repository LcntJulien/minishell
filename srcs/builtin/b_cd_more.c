/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:46:04 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/23 14:00:51 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_valid_path(char *str)
{
	struct stat	buf;

	return (stat(str, &buf));
}

int	valid_path(t_shell *mini, t_token *list, char *tmp_path)
{
	if (chdir(tmp_path) == -1)
	{
		mini->rtn = 1;
		if (list->s[0] == '-' && !list->s[1])
			ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: cd: ", tmp_path),
					": No such file or directory\n"), mini->out);
		else
			ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: cd: ", list->s),
					": No such file or directory\n"), mini->out);
		return (0);
	}
	else if (check_valid_path(tmp_path) == -1)
	{
		mini->rtn = 1;
		ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: cd: ", list->s),
				": Not a directory\n"), mini->out);
		return (0);
	}
	/* gerer les acces et droits */
	else
		return (1);
}
