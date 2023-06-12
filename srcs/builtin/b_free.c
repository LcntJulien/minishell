/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/12 22:54:49 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		free(tab);
	}
}

void	free_str(char *tmp)
{
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
}
