/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/05 20:16:35 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**sub_var_env(t_shell *mini, int lines, t_token *sub)
{
	char	**tmp;

	tmp = ft_calloc((lines + 1), sizeof(char *));
	if (!tmp)
		ft_exit(mini, 1);
	while (lines > 0)
	{
		if (ft_strncmp(mini->env[lines], sub->s, ft_strlen(mini->env[lines])))
			tmp[lines] = ft_strdup(mini->env[lines]);
		else
			tmp[lines] = ft_strdup(sub->s);
		lines--;
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
