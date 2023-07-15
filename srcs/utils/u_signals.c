/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:00:39 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/15 13:33:20 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	sigint_chose_handler(int s)
{
	(void)s;
	if (def_sig == 0)
		sigint_0_handler();
	//else if (def_sig == 1)
		//sigint_1_handler();
	//else if (def_sig == 2)
		//sigint_2_handler();
	//else if (def_sig == 1)
		//sigint_3_handler();
	//else if (def_sig == 1)
		//sigint_4_handler();
	//else if (def_sig == 1)
		//sigint_5_handler();
}

//static void	siquit_handler(int s)
//{
	//(void)s;
	//if (def_sig == FALSE)
	//{
		//rl_redisplay();
		//ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
		//rl_replace_line("", 0);
	//}
//}

void	define_signals(void)
{
	//struct sigaction	sigint;
	//struct sigaction	sigquit;
	
	//sigaction(SIGINT, &sigint, NULL);
	//sigaction(SIGINT, &sigquit, NULL);
	signal(SIGINT, sigint_chose_handler);
	//signal(SIGQUIT, sigquit_handler);
}