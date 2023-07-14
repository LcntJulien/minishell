/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/14 19:02:54 by jmathieu         ###   ########.fr       */
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

static void	not_a_variable(t_shell *mini)
{
	mini->rtn = 1;
	ft_putstr_fd("minishell: export: ", STDOUT_FILENO);
	ft_putstr_fd(mini->token->s, STDOUT_FILENO);
	ft_putstr_fd(": Not a valid identifier\n", STDOUT_FILENO);
}

void	b_export_args(t_shell *mini, t_token *list, int nb_args)
{
	int		lines;
	char	*var;

	while (nb_args > 0)
	{
		lines = tab_lines(mini->env);
		var = var_name(mini, list->s);
		if (!alpha_num_underscore(list->s))
			not_a_variable(mini);
		else if (alpha_num_underscore(list->s) == 2)
			continue ;
		else if (existing_var(mini, var) == -1)
			mini->env = add_var_env(mini, lines + 1, list);
		else
			sub_var_env(mini, lines, list);
		list = list->next;
		nb_args--;
		free_str(var);
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
