/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_split_ut.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:44:37 by jlecorne          #+#    #+#             */
/*   Updated: 2023/06/21 13:33:42 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**tabfree(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p[i]);
	free(p);
	return (NULL);
}

int	scount(const char *s, char c, int q)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	if (c == 0)
		return (1);
	while (s[i])
	{
		if (s[i] != 0 && s[i] != c && (s[i - 1] == c || i == 0))
		{
			if (q == 0)
				r++;
			if (s[i] == 34 || s[i] == 39)
				q = s[i];
		}
		i++;
		if (s[i] == q)
			q = 0;
	}
	return (r);
}
