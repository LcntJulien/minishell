/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:15:45 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/04 11:25:53 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_export_args()
{

}

char	**renew_env(t_shell *mini, int lines, int nb_args)
{
	int		i;
	int		flag;
	char	*var;
	char	**tmp;

	i = -1;
	flag = check_oldpwd(mini->env);
	if (flag == 1)
		tmp = ft_calloc((lines + 1), sizeof(char *));
	else
		tmp = ft_calloc((lines + 2), sizeof(char *));
	if (!tmp)
		ft_exit(mini, 0);
	while (mini->env[++i])
	{
		var = ft_strdup(mini->env[i]);
		tmp[i] = var;
	}
	oldpwd_status(mini, i, flag, 1);
	add_export_args();
	return (tmp);
}

void	b_env(t_shell *mini)
{
	int	i;
	
	//if (!mini->token->next || )
	i = -1;
	while (mini->env[++i])
		printf("%s\n", mini->env[i]);
}
