/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_history.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:17:11 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/21 16:21:42 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_history(int *histo)
{
	*histo = open(".mini_history", O_RDWR | O_APPEND | O_CREAT, 0644);
	if (histo == -1)
		return (0);
}