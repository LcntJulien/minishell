/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:54 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/06 08:50:00 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_nb_args(t_shell *mini, int i)
{
	t_token	*tmp;
	int		nb;

	nb = 0;
	tmp = mini->token;
	while (tmp->next && tmp->next->type == i)
	{
		nb++;
		tmp = tmp->next;
	}
	return (nb);
}

char	*var_name(char *str)
{
	int		i;
	int		j;
	char	*s;
	
	i = 0;
	j = 0;
	if (*str)
	{
		while (str[i] && str[i] != '=')
			i++;
		if (str[i] == '=')
			i--;
		s = calloc(sizeof(char), (i + 1));
		if (!s)
			return (0);
		while(str[j] && j < i)
		{
			s[j] = str[j]; 
			j++;
		}
		return (s);
	}
	return (0);
}

char	*var_content(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*s;
	
	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (str[i] && str[i] != '=')
		i++;
	i++;
	if (i == len)
		return (0);
	s = calloc(sizeof(char), (len - i + 1));
	if (!s)
		return (0);
	while(str[i] && i < len)
	{
		s[j] = str[i++];
		j++;
	}
	return (s);
}
