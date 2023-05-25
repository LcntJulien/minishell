/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:15:45 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/24 14:34:21 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env(t_shell *mini, char **tab)
{
	int	i;

	i = -1;
	while (mini->env[++i])
		printf("%s\n", mini->env[i]);
	return ;
}