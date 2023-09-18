/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_sig_hdrc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:03:34 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/18 18:41:03 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	sigint_hrdc0(int sig)
{
	(void)sig;
	g_sig = 42;
	rl_redisplay();
	exit(1);
}

static void	sigint_hrdc1(int sig)
{
	(void)sig;
	g_sig = 42;
	rl_redisplay();
	rl_replace_line("", 0);
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_redisplay();
	exit(1);
}

static void	sigquit_hrdc(int sig)
{
	(void)sig;
}

void	signals_hrdc(int i)
{
	if (i == 0)
		signal(SIGINT, sigint_hrdc0);
	else
		signal(SIGINT, sigint_hrdc1);
	signal(SIGQUIT, sigquit_hrdc);
}

void	replace_sig(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
