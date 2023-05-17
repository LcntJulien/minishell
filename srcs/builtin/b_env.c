/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:15:45 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/17 17:15:48 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Attention, le cas de l'argument 0 est faux, il faut prendre en compte
// les autres arguments, tels que les redirections, etc...
// Le renvoie et la sortie doit se faire aussi en fonction des arguments
void	env(t_shell *mini, char **tab)
{
	int	i;

	i = -1;
	while (mini->env[++i])
		printf("%s\n", mini->env[i]);		
}
