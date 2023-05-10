/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:libft/ft_strtrim.c
/*   Created: 2022/11/11 11:59:31 by jmathieu          #+#    #+#             */
/*   Updated: 2022/11/15 12:20:50 by jmathieu         ###   ########.fr       */
=======
/*   Created: 2022/11/10 11:44:49 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/04 20:34:53 by jlecorne         ###   ########.fr       */
>>>>>>> 2b58f5164b3ad6f5d88891129d3346018f6abe44:libft/srcs/ft_strtrim.c
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_isset(char s, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] != s)
			i++;
		else
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*s;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	while (s1[start] && ft_isset(s1[start], set) != 0)
		start++;
	while (start != end && ft_isset(s1[end - 1], set) != 0)
		end--;
	s = ft_calloc(sizeof(char), (end - start + 1));
	if (s == NULL)
		return (NULL);
	ft_strlcpy(s, &s1[start], (end - start + 1));
	return (s);
}
