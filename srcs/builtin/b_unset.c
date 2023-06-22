/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:40 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/22 20:03:27 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**delete_var(t_shell *mini, t_token *list, int i)
{
	int		j;
	int		len;
	char	**new_env;

	j = -1;
	len = tab_lines(mini->env) - 1;
	new_env = ft_calloc(sizeof(char *), (len + 1));
	if (!new_env)
		ft_exit_plus(mini, list, 0);
	len = -1;
	while (mini->env[++len])
	{
		if (len != i)
			new_env[++j] = mini->env[len];
	}
	return (new_env);
}

static void	b_unset_args(t_shell *mini, t_token *list, int nb_args)
{
	int	i;

	while (nb_args > 0)
	{
		i = existing_var(mini, list->s);
		if (i != -1)
			mini->env = delete_var(mini, list, i);
		mini->rtn = 0;
		list = list->next;
		nb_args--;
	}
	return ;
}

void	b_unset(t_shell *mini, t_token *list)
{
	int		nb_args;
	t_token	*tmp;

	nb_args = 0;
	if (!list->next)
		return ;
	else
	{
		tmp = mini->token->next;
		while (tmp && (tmp->type == 1 || tmp->type == 2))
		{
			nb_args++;
			tmp = tmp->next;
		}
		if (nb_args == 0)
			return ;
		list = mini->token->next;
		b_unset_args(mini, list, nb_args);
	}
}
