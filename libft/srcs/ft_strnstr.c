/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:58:16 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/10 14:44:42 by jmathieu         ###   ########.fr       */
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
