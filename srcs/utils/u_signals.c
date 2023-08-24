/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:33:06 by jmathieu          #+#    #+#             */
/*   Updated: 2023/08/24 18:17:08 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	define_last(t_shell *mini)
{
	if (g_sig == 131)
		mini->rtn = 131;
	else if (g_sig == 130)
		mini->rtn = 130;
	else if (g_sig == 1)
		mini->rtn = 1;
	g_sig = 0;
}

static void	sigint_chose_handler(int sig)
{
	(void)sig;
	if (g_sig == 0)
		sigint_0_handler();
	else if (g_sig == 1)
		sigint_1_handler();
	else if (g_sig == 2)
		sigint_2_handler();
}

static void	sigquit_handler(int sig)
{
	(void)sig;
	if (g_sig == 1)
	{
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
		rl_redisplay();
		g_sig = 131;
	}
	else if (g_sig == 2)
	{
		fprintf(stderr, "entre dans g_sig == 2\n");
		g_sig = 4;
	}
}

void	define_signals(void)
{
	signal(SIGINT, sigint_chose_handler);
	signal(SIGQUIT, sigquit_handler);
}
