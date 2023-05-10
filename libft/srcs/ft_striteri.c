/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:libft/ft_striteri.c
/*   Created: 2022/11/11 11:56:53 by jmathieu          #+#    #+#             */
/*   Updated: 2022/11/22 11:57:48 by jmathieu         ###   ########.fr       */
=======
/*   Created: 2022/11/15 18:25:37 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/04 20:35:00 by jlecorne         ###   ########.fr       */
>>>>>>> 2b58f5164b3ad6f5d88891129d3346018f6abe44:libft/srcs/ft_striteri.c
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
