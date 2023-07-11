/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/11 14:33:52 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sub_var_env(t_shell *mini, int lines, t_token *sub)
{
	int		i;

	i = 0;
	while (i < lines)
	{
		if (!ft_strncmp(var_name(mini, mini->env[i]),
				var_name(mini, sub->s), ft_strlen(sub->s)))
		{
			if ((is_there_an_equal(mini->env[i])
					&& is_there_an_equal(sub->s))
				|| (!is_there_an_equal(mini->env[i])
					&& is_there_an_equal(sub->s)))
			{
				mini->env[i] = sub->s;
				if (!mini->env[i])
				{
					ft_putstr_fd("No directory\n", STDOUT_FILENO);
					ft_exit_plus(mini);
					mini->rtn = -1;
					exit(mini->rtn);
				}
			}
		}
		i++;
	}
}

char	**add_var_env(t_shell *mini, int lines, t_token *new)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_calloc((lines + 1), sizeof(char *));
	if (!tmp)
	{
		ft_exit_plus(mini);
		exit(1);
	}
	while (mini->env[i])
	{
		tmp[i] = mini->env[i];
		i++;
	}
	tmp[i] = ft_strdup(new->s);
	if (!tmp[i])
	{
		ft_exit_plus(mini);
		exit(1);
	}
	return (tmp);
}
