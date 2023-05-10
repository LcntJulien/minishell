/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:37:14 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/10 15:43:41 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse(t_shell *mini)
{
	// char *line;
	// t_token *token;

    ft_putstr_fd((*mini).input, 1);
    ft_putchar_fd('\n', 1);
}