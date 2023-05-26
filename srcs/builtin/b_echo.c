/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:20 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/26 17:47:13 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	search_options(char *str, char c)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	if (!inside_quotes(str, i) && str[++i] != "-")
		return (0);
	while (str[++i] && str[i] < len)
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

void	b_echo(t_shell *mini)
{
	t_token	*list;
	int		i;

	i = 0;
	list = mini->token;
	if (!nb_args_no_redir(list, &i))
	{
		printf("\n");
		return ;
	}
	else
	{
		list = list->next;
		if (search_options(list->s, 'n'))
		{
			/* ecrire sans renvoie a la ligne tous les arguments*/
		}
		else
		{
			/* ecrire tous les arguments et renvoie a la ligne*/
		}
	}
	return ;
}
