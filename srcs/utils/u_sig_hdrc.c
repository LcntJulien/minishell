/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_sig_hdrc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:03:34 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/20 17:06:05 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	sigint_hrdc0(int sig)
{
	(void)sig;
	rl_redisplay();
	exit(1);
}

static void	sigint_hrdc1(int sig)
{
	(void)sig;
	// rl_redisplay();
	// rl_replace_line("", 0);
	// ft_putstr_fd("\n", STDERR_FILENO);
	// rl_redisplay();
	exit(1);
}

static void	sigquit_hrdc(int sig)
{
	(void)sig;
}

void	signals_hrdc(int i)
{
	(void)i;
	if (g_sig == 2)
		signal(SIGINT, sigint_hrdc1);
	else if (g_sig == 3)
		signal(SIGINT, sigint_hrdc0);
	signal(SIGQUIT, sigquit_hrdc);
}

void	replace_sig(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
