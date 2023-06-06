/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/06 08:15:17 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_existing_args(t_shell *mini, char *s)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], var_name(s), ft_strlen(var_name(s))))
			i++;
		else
			return (1);
	}
	return (0);
}

static int	alpha_num_underscore(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if(s[i] == '=' && i == 0)
			return (0);
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

void	b_export_args(t_shell *mini)
{
	int		lines;
	int		nb_args;
	t_token	*list;

	list = mini->token;
	nb_args = check_nb_args(mini, 1);
	list = list->next;
	while (nb_args > 0)
	{
		lines = tab_lines(mini->env);
		if (!alpha_num_underscore(list->s))
			printf("minishell: export: `%s': not a valid identifier\n", list->s);
		else if (!check_existing_args(mini, list->s))
			mini->env = add_var_env(mini, lines + 1, list);
		else
			mini->env = sub_var_env(mini, lines, list);
		list = list->next;
		nb_args--;
	}
	free(list);
}

void	b_export(t_shell *mini)
{
	if (!mini->token->next || !check_nb_args(mini, 1))
		print_listed_env(mini);
	else
		b_export_args(mini);
}
