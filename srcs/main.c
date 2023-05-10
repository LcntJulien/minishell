/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:07:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/10 15:40:57 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	t_shell	mini;
	char	*excmd;

	excmd = "exit";
	mini.in = dup(STDIN_FILENO);
	mini.out = dup(STDOUT_FILENO);
	mini.rtn = 0;
	mini.exit = 0;
	while (mini.exit == 0)
	{
		mini.input = readline("minishell $ ");
		if (ft_strncmp(excmd, mini.input, ft_strlen(mini.input)) == 0)
			mini.exit = 1;
		parse(&mini);
	}
	free(mini.input);
	return (0);
}
