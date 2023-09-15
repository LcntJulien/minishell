/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_sig_hdrc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:03:34 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/15 12:25:00 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_hrdc(int sig)
{
	fprintf(stderr, "g_sig int hrdc = %d\n", g_sig);
	(void)sig;
	rl_replace_line("", 0);
	exit(1);
}

void	sigquit_hrdc(int sig)
{
	fprintf(stderr, "g_sig quit hrdc = %d\n", g_sig);
	(void)sig;
}

void	signals_hrdc(void)
{
	signal(SIGINT, sigint_hrdc);
	signal(SIGQUIT, sigquit_hrdc);
}
