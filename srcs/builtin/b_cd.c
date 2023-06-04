/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:06 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/04 09:37:31 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_cd(t_shell *mini)
{
	int		i;
	char	*path;

	path = mini->token->next->s;
	if (chdir(path) == -1)
	{
		printf("Invalid path");
		return ;
	}
	i = 0;
	while (mini->env[i] && !ft_strncmp(mini->env[i], "PWD", 3))
		i++;	
	//mini->env[i] = ft_strdup(path);
	return ;
}
