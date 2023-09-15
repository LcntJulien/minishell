/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_sig_hdrc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:03:34 by jmathieu          #+#    #+#             */
/*   Updated: 2023/09/15 14:50:50 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_hrdc(int sig)
{
	printf("here int hrdc?\n");
	(void)sig;
	g_sig = 4;
	exit(1);
}

void	sigquit_hrdc(int sig)
{
	printf("here quit hrdc?\n");
	(void)sig;
}

void	signals_hrdc(void)
{
	signal(SIGINT, sigint_hrdc);
	signal(SIGQUIT, sigquit_hrdc);
}
