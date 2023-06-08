/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/08 13:31:18 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tab(char **tab)
{
	int i;

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
