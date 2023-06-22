/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_history.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:17:11 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/22 19:03:05 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_histo(char *str, int histo)
{
	add_history(str);
	if (histo <= 0)
		return ;
	write(histo, str, ft_strlen(str));
	write(histo, "\n", 1);
}

int	create_history(int *histo)
{
	*histo = open(".mini_history", O_RDWR | O_APPEND | O_CREAT, 0644);
	if (*histo == -1)
		return (0);
	return (1);
}
