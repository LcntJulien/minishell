/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:45:27 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/04 11:55:08 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redirin(void)
{
	// exit(1);
}

void	redirout(void)
{
	// exit(1);
}

int	is_redir(t_token *tk)
{
	t_token	*cpy;
	int		tab[11];
	int		i;

	cpy = tk;
	i = 0;
	while (tab[i] && i <= 11)
		tab[i++] = 0;
	while (cpy && cpy->type != PIPE)
	{
		if (cpy->type == INPUT)
			tab[INPUT]++;
		if (cpy->type == OUTPUT)
			tab[OUTPUT]++;
		if (cpy->type == APPEND)
			tab[APPEND]++;
		if (cpy->type == HEREDOC)
			tab[HEREDOC]++;
		cpy = cpy->next;
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
	return (0);
}
