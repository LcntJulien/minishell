/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:59:31 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/10 14:44:51 by jmathieu         ###   ########.fr       */
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
