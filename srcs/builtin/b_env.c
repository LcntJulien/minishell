/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:15:45 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/03 11:02:20 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_env(t_shell *mini)
{
	int	i;
	
	i = -1;
	while (mini->env[++i])
	{
		if (ft_strchr(mini->env[i], '=') != NULL)
		{
			printf("%s", mini->env[i]);
			if (mini->env[i + 1])
				printf("\n");	
		}
	}
	printf("\n");
}
