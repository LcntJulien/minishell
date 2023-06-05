/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/05 15:50:30 by jmathieu         ###   ########.fr       */
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
	while (s[i] && s[i] != '=')
	{
		if ((s[i] >= '0' && s[i] >= '9')
		|| (s[i] >= 'A' && s[i] >= 'Z')
		|| (s[i] >= 'a' && s[i] >= 'z')
		|| s[i] == '_')
			i++;
		else
			return (0);
	}
	if (s[i] == '=')
		return (1);
	return (0);
}

void	b_export_arg(t_shell *mini)
{
	int		i;
	int		lines;
	int		nb_args;
	t_token	*tmp;

	i = -1;
	tmp = mini->token;
	nb_args = check_nb_args(mini, 1);
	tmp = tmp->next;
	printf("%s\n", tmp->s);
	while (nb_args > 0)
	{
		if (!alpha_num_underscore(tmp->s))
			printf("error to handle");
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
	{
		b_export_arg(mini);
	}
}
