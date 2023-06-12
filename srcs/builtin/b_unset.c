/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:40 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/12 19:44:56 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_variable(t_shell *mini, t_token *list, int i)
{
	if (ft_strncmp(list->s, "HOME", 4) == 0)
	{
		mini->home = mini->env[i];
		return (1);
	}
	else
		return (0);
}

void	del_var_env(t_shell *mini, char **env, int lines, t_token *list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i != lines)
	{
		env[j] = mini->env[i];
		i++;
		j++;
	}
	check_variable(mini, list, i);
	i++;
	while (mini->env[i])
	{
		env[j] = mini->env[i];
		i++;
		j++;
	}
}

static char	**delete_var(t_shell *mini, t_token *list, char *var)
{
	int		i;
	int		len;
	char	**new_env;

	i = -1;
	while (mini->env[++i])
	{
		len = ft_strlen(var_name(mini, mini->env[i]));
		if (ft_strncmp(var_name(mini, mini->env[i]), var, len) == 0)
		{
			len = tab_lines(mini->env) - 1;
			new_env = ft_calloc(sizeof(char *), (len + 1));
			if (!new_env)
				ft_exit_plus(mini, list, 0);
			del_var_env(mini, new_env, i, list);
		}
	}
	return (new_env);
}

void	b_unset(t_shell *mini, t_token *list)
{
	int	i;

	if (!list->next)
		return ;
	else
	{
		list = list->next;
		i = check_nb_args(mini, 1);
		while (i > 0)
		{
			if (ft_strncmp(list->s, "_", ft_strlen(list->s) != 0))
			{
				if (existing_var(mini, list->s) != -1)
					mini->env = delete_var(mini, list, list->s);
			}
			list = list->next;
			i--;
		}
	}
	mini->rtn = 0;
	return ;
}
