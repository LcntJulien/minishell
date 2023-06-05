/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/05 15:10:13 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**sub_var_env(t_shell *mini, int lines, t_token *sub)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_calloc((lines + 1), sizeof(char *));
	if (!tmp)
		ft_exit(mini, 0);
	while (mini->env[i])
	{
		if (!check_existing_args(mini, sub->s))
			tmp[i] = ft_strdup(mini->env[i]);
		else
			tmp[i] = ft_strdup(sub->s);
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
		i++;
	}
	tmp[i] = ft_strdup(new->s);
	return (tmp);
}
