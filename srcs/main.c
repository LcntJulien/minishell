/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:07:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/06 15:43:24 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	t_shell	mini;

	char	*excmd = "exit";
	while (1)
	{
		mini.input = readline("minishell $ ");
		if (ft_strncmp(excmd, mini.input, ft_strlen(mini.input)) == 0)
			break;
		if (mini.input)
			printf("%s\n", mini.input);
	}
	free(mini.input);
	return (0);
}
