
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_sig_forked.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:03:34 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/15 12:05:14 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_forked(void)
{
	printf("sigint forked\n");
	printf("g_sig = %d\n", g_sig);
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_redisplay();
	g_sig = 130;
}

void	sigquit_forked(void)
{
	printf("sigquit forked\n");
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	rl_redisplay();
	g_sig = 131;
}

void	sigint_piped(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDERR_FILENO);
	g_sig = 300;
}

void	sigquit_piped(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	g_sig = 301;
}

void	piped_sig(void)
{
	signal(SIGINT, sigint_piped);
	signal(SIGQUIT, sigquit_piped);
}