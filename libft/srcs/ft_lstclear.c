/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:libft/ft_lstclear.c
/*   Created: 2022/11/22 09:25:14 by jmathieu          #+#    #+#             */
/*   Updated: 2022/11/22 09:25:16 by jmathieu         ###   ########.fr       */
=======
/*   Created: 2023/04/17 17:17:27 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/04 20:35:17 by jlecorne         ###   ########.fr       */
>>>>>>> 2b58f5164b3ad6f5d88891129d3346018f6abe44:libft/srcs/ft_lstclear.c
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;

	if (lst)
	{
		while (*lst)
		{
			elem = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = elem;
		}
		*lst = NULL;
	}
}
