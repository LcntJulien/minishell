/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:52:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/24 17:23:40 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	parse(t_shell *mini)
{
	
}

static void	search(t_shell *mini)
{
	
}

static before_split(t_shell *mini)
{
	
}

void	divide_args(t_shell *mini)
{
	int		i;

	before_split(mini);
	mini->line = ft_split(mini->input, ' ');
	if (!mini->line)
		ft_exit(mini, 0);
	i = 1;
	while (mini->line[i])
		i++;
	if (i == 2 && !mini->line[2])
		search(mini);
	else
		parse(mini);
}
