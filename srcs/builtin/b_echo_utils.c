/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:17:43 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/27 12:31:45 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_print_arg(char *str, int q, t_shell *mini)
{
	int i;

	i = -1;
	if (q == 0)
	{
		while (str[++i])
		{
			if (str[i] == '$' && is_variable(str, i + 1, mini))

			else
				ft_putchar_fd(str[i], 1);
		}
	}
}
