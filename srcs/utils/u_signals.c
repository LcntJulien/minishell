/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:00:39 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/18 10:51:32 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	sigint_chose_handler(int s)
{
	(void)s;
	if (def_sig == 0)
		sigint_0_handler();
	else if (def_sig == 1)
		sigint_1_handler();
}

static void	sigquit_handler(int s)
{
	(void)s;
	if (def_sig != 0)
	{
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
		rl_redisplay();
		def_sig = 0;
	}
}

void	define_signals(void)
{
	signal(SIGINT, sigint_chose_handler);
	signal(SIGQUIT, sigquit_handler);
}
