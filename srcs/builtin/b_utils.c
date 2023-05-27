/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:53:47 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/27 12:32:27 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	nb_args_no_redir(t_token *args, int i)
{
	while (args->next->s)
	{
		i++;
		args = args->next;
	}
	return (i);
}

int	inside_quotes(char *str)
{
	int i;

	i = 0;
	if (str[i] == '\'')
	{
		while (str[i])
			i++;
		i--;
		if (str[i] != '\'')
			return (0);
		else
			return (1);
	}
	else if (str[i] == "\"")
	{
		while (str[i])
			i++;
		i--;
		if (str[i] != "\"")
			return (0);
		else
			return (2);
	}
}

static char	*define_word(char *str, int i, t_shell *mini)
{
	int 	j;
	int		k;
	char	*word;

	j = 0;
	k = 0;
	while (str[i] && str[i] != ' ')
		j++;
		i++;
	i = i - j;
	word = ft_calloc((j + 1), sizeof(char));
	if (!word)
		ft_exit(mini, 1);
	while(j >= 0)
	{
		word[k++] = str[i++];
		j--;
	}
	word[k] = '\0';
	return (word);
}

bool	is_variable(char *str, int i, t_shell *mini)
{
	int		j;
	int		len;
	char	*new_w;

	j = 0;
	new_w = define_word(str, i, mini);
	len = ft_strlen(new_w);
	while (mini->env[j])
	{
		if (ft_strncmp(new_w, mini->env[j], len))
		// a completer 
	}
}
