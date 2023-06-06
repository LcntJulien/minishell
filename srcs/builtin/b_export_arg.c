/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/06 08:51:22 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**sub_var_env(t_shell *mini, int lines, t_token *sub)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc((lines + 1), sizeof(char *));
	if (!tmp)
		ft_exit(mini, 1);
	while (i < lines)
	{
		while (mini->env[i][j] != '=')
			j++;
		if (ft_strncmp(var_name(mini->env[i]), var_name(sub->s), j))
			tmp[i] = ft_strdup(mini->env[i]);
		else
			tmp[i] = ft_strdup(sub->s);
		if (!tmp[i])
			ft_exit_plus(mini, sub, 0);
		i++;
	}
	return (tmp);
}


char	**add_var_env(t_shell *mini, int lines, t_token *new)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_calloc((lines + 1), sizeof(char *));
	if (!tmp)
		ft_exit(mini, 0);
	while (mini->env[i])
	{
		tmp[i] = ft_strdup(mini->env[i]);
		if (!tmp[i])
		{
			free(new);
			ft_exit(mini, 1);
		}
		i++;
	}
	tmp[i] = ft_strdup(new->s);
	return (tmp);
}
