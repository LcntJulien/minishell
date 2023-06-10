/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_exce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 08:16:28 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/10 08:18:52 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	modify_oldpwd(t_shell *mini, t_token *list)
{
	int	i;

	i = -1;
	while (mini->env[++i])
	{
		if (ft_strncmp(mini->env[i], "PWD", 3) == 0)
		{
			mini->env[i] = ft_strjoin("PWD=", list->s);
			break ;
		}
		else
			i++;
	}
	mini->rtn = 0;
}

void	modify_pwd(t_shell *mini, t_token *list)
{
	int	i;
	char *tmp;

	i = -1;
	while (mini->env[++i])
	{
		if (ft_strncmp(mini->env[i], "PWD", 3) == 0)
			tmp = var_content(mini, mini->env[i]);
	}
	i = -1;
	while (mini->env[++i])
	{
		if (ft_strncmp(mini->env[i], "OLDPWD", 6) == 0)
		{
			mini->env[i] = ft_strjoin("OLDPWD=", tmp);
			break ;
		}
	}
	modify_oldpwd(mini, list);
}
