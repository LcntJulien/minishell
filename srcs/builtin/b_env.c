/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 15:48:25 by jmathieu          #+#    #+#             */
/*   Updated: 2023/08/30 22:52:38 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	define_var(t_shell *mini, int i)
{
	char	*pwd;
	char	*str;
	
	free_str(mini->env[i]);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_exit_plus(mini, "Fail to access directory\n", 1);
	str = ft_strjoin("_=", pwd);
	free_str(pwd);
	mini->env[i] = ft_strjoin(str, "/env");
	free_str(str);
}

void	b_env(t_shell *mini)
{
	int		i;
	t_token	*list;

	list = mini->token;
	if (!list->next || (list->next && (list->next->type == 6
				|| list->next->type == 8 || list->next->type == 9)))
	{
		i = -1;
		while (mini->env[++i])
		{
			if (!ft_strncmp("_=", mini->env[i], 2))
				define_var(mini, i);
			if (is_there_an_equal(mini->env[i]))
			{
				ft_putstr_fd(mini->env[i], STDOUT_FILENO);
				ft_putstr_fd("\n", STDOUT_FILENO);
			}
		}
		mini->rtn = 0;
	}
	else
		mini->rtn = 1;
	return ;
}
