/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:53:11 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/25 17:02:35 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pre_builtin(t_shell *mini)
{
	t_token	*list;

	if (token)
	list = mini->token;
	while (list && !strncmp(list->next->s, "export", 6))
		list = list->next;
	if (list->next && strncmp(list->next->s, ">", 1))
		redir_export(mini);
}
