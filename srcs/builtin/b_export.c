/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/05 19:21:26 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_existing_args(t_shell *mini, char *s)
{
	int	i;

	i = 0;
	// PROBLEME HERE !!!!
	while (mini->env[i])
	{
		if (ft_strlen(mini->env[i]) > ft_strlen(s))
		{
			if (ft_strncmp(mini->env[i], var_name(s), ft_strlen(mini->env[i])))
				i++;
			else
				return (1);
		}
		else
		{
			if (ft_strncmp(var_name(s), mini->env[i],
			ft_strlen(var_name(s))))
				i++;
			else
				return (1);
		}
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
	t_token	*tmp;

	lines = 0;
	tmp = mini->token;
	nb_args = check_nb_args(mini, 1);
	tmp = tmp->next;
	while (nb_args > 0)
	{
		if (!alpha_num_underscore(tmp->s))
			printf("minishell: export: `%s': not a valid identifier\n", tmp->s);
		if (!check_existing_args(mini, tmp->s))
		{
			lines = tab_lines(mini->env) + 1;
			mini->env = add_var_env(mini, lines, tmp);
		}
		else
			mini->env = sub_var_env(mini, lines, tmp);
		tmp = tmp->next;
		nb_args--;
	}
}

void	b_export(t_shell *mini)
{
	if (!mini->token->next || !check_nb_args(mini, 1))
		print_listed_env(mini);
	else
		b_export_args(mini);
}
