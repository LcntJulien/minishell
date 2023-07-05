/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:00:39 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/05 18:07:18 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	// ft_putstr_fd("\033[0;35m\033[1mminishell ▸ \033[0m", 2);
	// printf("Received SIGINT signal (%d)\n", sig);
	// system("leaks minishell");
	exit(0);
}

void	define_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
}