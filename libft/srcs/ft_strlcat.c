/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:57:14 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/10 14:44:11 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (!dst && !dstsize)
		return (0);
	i = ft_strlen(dst);
	k = i + ft_strlen(src);
	if (i > dstsize || (dstsize == 0 && i == 0))
		return (dstsize + ft_strlen(src));
	j = 0;
	while ((i + 1) < dstsize && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (k);
}
