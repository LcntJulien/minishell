/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo_more.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:26:29 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/08 18:09:42 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_opt(t_token *list, int nb_opt)
{
	int nb_retain;

	nb_retain = nb_opt;
	while (list && nb_opt > 0)
	{
		nb_opt--;
		list = list->next;
	}
	if (!list)
		return (0);
	return (1);
}
