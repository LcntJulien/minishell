/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/23 14:33:35 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	alpha_num_underscore(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[0] == '=')
			return (0);
		else if (s[0] == '_' && s[1] == '=')
			return (2);
		else if (ft_isalnum(s[i]) || s[i] == '_')
			i++;
		else if (s[i] == '=')
			break ;
		else
			return (0);
	}
	if (s[i] == '=' || !s[i])
		return (1);
	return (0);
}

void	b_export_args(t_shell *mini, t_token *list, int nb_args)
{
	int		lines;

	while (nb_args > 0)
	{
		lines = tab_lines(mini->env);
		if (!alpha_num_underscore(list->s))
		{
			mini->rtn = 1;
			ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: export: ", list->s),
					": Not a valid identifier\n"), mini->out);
		}
		else if (alpha_num_underscore(list->s) == 2)
		{	
			mini->rtn = 0;
			break ;
		}
		else if (existing_var(mini, var_name(mini, list->s)) == -1)
			mini->env = add_var_env(mini, lines + 1, list);
		else
			sub_var_env(mini, lines, list);
		list = list->next;
		nb_args--;
	}
}

void	b_export(t_shell *mini, t_token *list)
{
	int		nb_args;

	if (!mini->token->next || !check_nb_args(mini, 1))
		print_listed_env(mini);
	else
	{
		list = mini->token;
		nb_args = check_nb_args(mini, 1);
		list = list->next;
		b_export_args(mini, list, nb_args);
	}
}
