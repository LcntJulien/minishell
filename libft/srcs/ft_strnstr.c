/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:libft/ft_strnstr.c
/*   Created: 2022/11/11 11:58:16 by jmathieu          #+#    #+#             */
/*   Updated: 2022/11/22 11:06:43 by jmathieu         ###   ########.fr       */
=======
/*   Created: 2022/11/09 15:52:53 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/04 20:34:55 by jlecorne         ###   ########.fr       */
>>>>>>> 2b58f5164b3ad6f5d88891129d3346018f6abe44:libft/srcs/ft_strnstr.c
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (!haystack && !len)
		return (NULL);
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[i] && ft_strlen(needle) <= len - i)
	{
		if (haystack[i] == needle[0])
		{
			if (ft_strncmp(haystack + i, needle, ft_strlen(needle)) == 0)
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (0);
}
