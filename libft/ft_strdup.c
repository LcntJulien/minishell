/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:27:38 by jlecorne          #+#    #+#             */
/*   Updated: 2023/04/18 13:11:45 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;

	if (s1[0] == '\0')
		return (ft_calloc(1, sizeof(char)));
	p = (char *)malloc(ft_strlen(s1) + 1);
	if (!p)
		return (NULL);
	ft_memcpy(p, s1, (ft_strlen(s1) + 1));
	return (p);
}
