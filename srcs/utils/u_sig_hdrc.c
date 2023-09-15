/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_sig_hdrc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:03:34 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/15 15:59:22 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_hrdc(int sig)
{
	printf("sigint hrdc\n");
	(void)sig;
	g_sig = 42;
	exit(1);
}

void	sigquit_hrdc(int sig)
{
	printf("sigquit hrdc\n");
	(void)sig;
}

void	signals_hrdc(void)
{
	signal(SIGINT, sigint_hrdc);
	signal(SIGQUIT, sigquit_hrdc);
}

void	sigint_b_hrdc(int sig)
{
	(void)sig;
}

void	sigquit_b_hrdc(int sig)
{
	(void)sig;
}

void	signals_b_hrdc(void)
{
	signal(SIGINT, sigint_b_hrdc);
	signal(SIGQUIT, sigquit_b_hrdc);
}
