/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:53:47 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/26 16:55:58 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	nb_args_no_redir(t_token *args, int i)
{
	while (!args->next->s)
	{
		i++;
		args = args->next;
	}
	return (i);
}

void	search_options()
{

}
