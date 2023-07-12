/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:00:39 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/12 20:25:35 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	sigint_handler(int sig)
{
	(void)sig;
	if (define_signal == TRUE)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	sigquit_handler(int sig)
{
	(void)sig;
	if (define_signal == FALSE)
	{
		rl_redisplay();
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
		rl_replace_line("", 0);
	}
}

void	define_signals(void)
{
	//struct sigaction	sigint;
	//struct sigaction	sigquit;
	
	//sigaction(SIGINT, &sigint, NULL);
	//sigaction(SIGINT, &sigquit, NULL);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}