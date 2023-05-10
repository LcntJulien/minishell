/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:07:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/10 12:14:30 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av)
{
	char	*line;
	(void)ac;
	(void)av;

	line = readline("> ");
	
	//while ((line = readline("> ")) != NULL)
	//{
        //if (strcmp(line, "exit") == 0)
		//{
            //free(line);
            //break;
        //}
        //printf("You entered: %s\n", line);
        //add_history(line);
        //free(line);
    //}
	return (0);
}
