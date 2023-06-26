/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:45:27 by jlecorne          #+#    #+#             */
/*   Updated: 2023/06/26 14:50:08 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redirin(void)
{
	exit(1);
}

void	redirout(void)
{
	exit(1);
}

int	is_redir(t_token *tk)
{
	int tab[11];

	while (tk && tk->type != PIPE)
	{
		if (tk->type == INPUT)
			tab[INPUT]++;
		if (tk->type == OUTPUT)
			tab[OUTPUT]++;
		if (tk->type == APPEND)
			tab[APPEND]++;
		if (tk->type == HEREDOC)
			tab[HEREDOC]++;
	}
	if (tab[INPUT] >= 1 || tab[HEREDOC] >= 1 || tab[OUTPUT] >= 1
		|| tab[APPEND] >= 1)
	{
		if (tab[INPUT] >= 1 || tab[HEREDOC] >= 1)
			redirin();
		if (tab[OUTPUT] >= 1 || tab[APPEND] >= 1)
			redirout();
		return (1);
	}
	else
		return (0);
}
