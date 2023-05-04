/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:59:46 by jmathieu          #+#    #+#             */
/*   Updated: 2022/11/11 11:59:48 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	t;

	if (s == 0 || start >= ft_strlen(s))
		return ((char *)ft_calloc(1, sizeof(char)));
	if (ft_strlen(s + start) < len)
	{
		ptr = ft_calloc(ft_strlen(s + start) + 1, sizeof(char));
		t = (ft_strlen(s + start) + 1);
	}
	else
	{
		ptr = ft_calloc(len + 1, sizeof(char));
		t = (len + 1);
	}
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, &s[start], t);
	return (ptr);
}
