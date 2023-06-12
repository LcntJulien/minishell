/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:53:47 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/12 19:48:53 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tab_lines(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	is_there_an_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		else
			i++;
	}
	return (0);
}

int	max_len(int s1, int s2)
{
	if (s1 >= s2)
		return (s1);
	else
		return (s2);
}

int	check_nb_args(t_shell *mini, int i)
{
	t_token	*tmp;
	int		nb;

	nb = 0;
	tmp = mini->token;
	while (tmp->next && tmp->next->type == i)
	{
		nb++;
		tmp = tmp->next;
	}
	return (nb);
}
