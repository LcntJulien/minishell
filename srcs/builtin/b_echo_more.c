/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo_more.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:26:29 by jmathieu          #+#    #+#             */
/*   Updated: 2023/08/24 13:00:33 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*define_word(char *str, int i)
{
	char	*tmp_str;
	int		j;

	j = 0;
	tmp_str = ft_calloc(sizeof(char), ft_strlen(str));
	if (!str)
		return (NULL);
	while (str[i])
	{
		tmp_str[j++] = str[i];
		i++;
	}
	return (tmp_str);
}

static void	other_variable(t_shell *mini, t_token *tmp, int i)
{
	if (tmp->s[i] == '$')
	{
		free_str(tmp->s);
		tmp->s = ft_strdup(ft_itoa(getpid()));
	}
	else if (tmp->s[i] == '_')
	{
		free_str(tmp->s);
		tmp->s = return_var_content(mini, "_");
	}
	else
	{
		free_str(tmp->s);
		tmp->s = ft_strdup(ft_itoa(mini->rtn));
	}
}

/* a supprimer une fois le parsing ok */
void	is_it_a_variable(t_shell *mini, t_token *tmp)
{
	int		i;
	char	*tmp_str;

	i = 0;
	if (tmp->s[i++] == '$')
	{
		if (tmp->s[i] == '?' || tmp->s[i] == '$' || tmp->s[i] == '_')
			other_variable(mini, tmp, i);
		tmp_str = define_word(tmp->s, i);
		if (!tmp_str)
			ft_exit_plus(mini, "Fail to allocate memory\n", 1);
		free_str(tmp_str);
	}
}

int	check_opt(t_token *list, int nb_opt)
{
	while (list && nb_opt > 0)
	{
		nb_opt--;
		list = list->next;
	}
	if (!list)
		return (0);
	return (1);
}
