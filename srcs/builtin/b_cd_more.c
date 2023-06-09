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

void	parent_folder(t_shell *mini, t_token *list)
{
	char	*path;
	int		len;

	path = getcwd(NULL, 0);
	len = ft_strlen(path);
	while (path[len] != '/' && len > 0)
		len--;
	if (len == 0)
		
}