/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:33:06 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/18 15:16:11 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	define_last(t_shell *mini)
{
	if (g_sig == 131)
		mini->rtn = 131;
	else if (g_sig == 130)
		mini->rtn = 130;
	else if (g_sig == 20)
		mini->rtn = 1;
	g_sig = 0;
}

static void	sigint_chose_handler(int sig)
{
	(void)sig;
	//printf("g_sig = %d\n", g_sig);
	if (g_sig == 0)
		sigint_0_handler();
	else
		sigint_1_handler();
}

static void	sigquit_handler(int sig)
{
	(void)sig;
	if (g_sig != 0)
	{
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
		rl_redisplay();
		g_sig = 131;
	}
}

void	define_signals(void)
{
	signal(SIGINT, sigint_chose_handler);
	signal(SIGQUIT, sigquit_handler);
}
