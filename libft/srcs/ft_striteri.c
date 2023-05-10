/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:56:53 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/10 14:45:18 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int		i;

	i = 0;
	if (s != 0 && f != 0)
	{
		while (s[i])
		{
			f(i, &s[i]);
			i++;
		}
	}
}
