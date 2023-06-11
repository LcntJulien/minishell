/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 10:46:04 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/11 11:22:46 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*substract_folder_name(t_shell *mini, t_token *list)
{
	int		i;
	int		len;
	char	*folder_name;

	i = 0;
	len = ft_strlen(list->s);
	while (list->s[i] && list->s[i] == '/')
		i++;
	folder_name = calloc(sizeof(char *), (len - i + 1));
	if (!folder_name)
		ft_exit_plus(mini, list, 0);
	while (i < len)	
	{
		folder_name[i] = list->s[i];
		i++;
	}
	return (folder_name);	
}

char	*home_path(t_shell *mini, t_token *list)
{
	char	*home;

	home = var_content(mini, "HOME");
	if (!home)
		return ("HOME");
	else if (list->s[1] && list->s[1] == '/')
		return (ft_strjoin(home, substract_folder_name(mini, list)));
	return (list->s);
}

char	*old_pwd(t_shell *mini, t_token *list)
{
	int		i;
	
	(void)list;
	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], "OLDPWD", 6) == 0)
			return (var_content(mini, mini->env[i]));
		else
			i++;
	}
	return ("OLDPWD");
}
