/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/05 09:29:29 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_export_args()
{

	while (i <= lines)
	{
		var = ft_strdup(mini->env[i]);
		tmp[i] = var;
	}
}

char	**renew_env(t_shell *mini, int lines, int nb_args)
{
	int		i;
	char	*var;
	char	**tmp;

	i = 0;
	tmp = ft_calloc((lines + 1), sizeof(char *));
	if (!tmp)
		ft_exit(mini, 0);
	while (mini->env[i])
		i++;
	add_export_args(mini, tmp, lines, i);
	return (tmp);
}
