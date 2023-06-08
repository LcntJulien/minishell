/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:53:47 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/08 12:36:37 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tab_lines(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	is_there_an_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		else
			i++;
	}
	return (0);
}

int	max_len(int s1, int s2)
{
	if (s1 >= s2)
		return (s1);
	else
		return (s2);
}

char	*define_word(char *str, int i, t_shell *mini)
{
	int 	j;
	int		k;
	char	*word;

	j = 0;
	k = 0;
	while (str[i] && str[i] != ' ')
	{
		j++;
		i++;
	}
	i = i - j;
	word = ft_calloc((j + 1), sizeof(char));
	if (!word)
		ft_exit(mini, 1);
	while(j > 0)
	{
		word[k++] = str[i++];
		j--;
	}
	word[k] = '\0';
	return (word);
}

int	is_variable(char *str, int i, t_shell *mini, int *len)
{
	int		j;
	char	*new_w;

	j = 0;
	new_w = define_word(str, i + 1, mini);
	*len = ft_strlen(new_w);
	while (mini->env[j])
	{
		i = ft_strncmp(new_w, mini->env[j], (size_t)len);
		if (i == 0)
			break ;
		else
			j++;
	}
	free(new_w);
	if (i == 0)
		return (j);
	else
		return (0);
}
