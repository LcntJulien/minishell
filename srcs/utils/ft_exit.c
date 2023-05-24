/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:11:51 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/24 16:19:20 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(t_shell *mini, int i)
{
	int	j;

	j = -1;
	if (i == 0)
	{
		while (mini->env[++i])
			free(mini->env[i]);
		printf("Trouble splitting arguments !\n");
		exit(0);
	}
}
