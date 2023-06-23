/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_history.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:17:11 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/23 09:02:31 by jmathieu         ###   ########.fr       */
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

static void	init_history(int *histo)
{
	char	*str;
	char	*s;

	str = get_next_line(*histo);
	if (!str)
		return ;
	while (str)
	{	
		s = ft_substr(str, 0, ft_strlen(str) - 1);
		add_history(s);
		free(str);
		free(s);
		str = get_next_line(*histo);
	}
}

int	create_history(int *histo)
{
	*histo = open(".mini_history", O_RDWR | O_APPEND | O_CREAT, 0644);
	if (*histo == -1)
		return (0);
	init_history(histo);
	return (1);
}
