/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 11:17:43 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/27 17:48:19 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_variable(t_shell *mini, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (mini->env[i][j] && mini->env[i][j] != '=')
		j++;
	while (mini->env[i][++j])
	{
		ft_putchar_fd(mini->env[i][j], 1);
		k++;
	}
	if (k == 0)
		return (0);
	return (j);
}

bool	without_quote_print(char *str, t_shell *mini)
{
	int i;
	int	j;
	int	var;

	i = -1;
	while (str[++i])
	{
		var = 0;
		if (str[i] == '$' && str[i + 1] == '$')
		{
			var = getpid();
			printf("%d", var);
			i++;
		}
		else if (str[i] == '$' && is_variable(str, i, mini, &var) != 0)
		{
			j = print_variable(mini, var);
			if (j == 0)
				return (false);
			i = i + j - 1;
		}
		else	
			ft_putchar_fd(str[i], 1);
	}
	return (true);
}

bool	with_squote_print(char *str, t_shell *mini)
{
	int i;
	int	j;
	int	var;

	i = -1;
	while (str[++i])
	{
		var = 0;
		if (str[i] == '$' && is_variable(str, i, mini, &var) != 0)
		{
			j = print_variable(mini, var);
			if (j == 0)
				return (false);
			i = i + j - 1;
		}
		else	
			ft_putchar_fd(str[i], 1);
	}
	return (true);
}

bool	with_dquote_print(char *str, t_shell *mini)
{
	int i;
	int	j;
	int	var;

	i = -1;
	while (str[++i])
	{
		var = 0;
		if (str[i] == '$' && str[i + 1] == '$')
		{
			var = getpid();
			printf("%d", var);
			i++;
		}
		else if (str[i] == '$' && is_variable(str, i, mini, &var) != 0)
		{
			j = print_variable(mini, var);
			if (j == 0)
				return (false);
			i = i + j - 1;
		}
		else	
			ft_putchar_fd(str[i], 1);
	}
	return (true);
}
