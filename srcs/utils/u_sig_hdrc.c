/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_sig_hdrc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:03:34 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/18 13:13:49 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	sigint_hrdc(int sig)
{
	(void)sig;
	g_sig = 42;
	exit(1);
}

static void	sigquit_hrdc(int sig)
{
	(void)sig;
}

void	signals_hrdc(void)
{
	signal(SIGINT, sigint_hrdc);
	signal(SIGQUIT, sigquit_hrdc);
}

void	replace_sig(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
