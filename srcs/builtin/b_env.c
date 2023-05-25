/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:15:45 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/25 14:54:55 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env(t_shell *mini)
{
	int	i;
	
	i = -1;
	while (mini->env[++i])
	{
		if (!strncmp(mini->env[i], "OLDPWD=", 7))
			break ;
		else
			printf("%s\n", mini->env[i]);
	}
}
