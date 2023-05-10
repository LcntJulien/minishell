/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:52:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/10 15:53:00 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse(t_shell *mini)
{
	char *line;
	t_token *token;

	(void) line;
	(void)	token;
    ft_putstr_fd((*mini).input, 1);
}