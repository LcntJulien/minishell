/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:26 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/11 23:05:32 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//void	exit_until(t_shell *mini)
//{
	//if (mini->home)
		//free_str(mini->home);
	//if (mini->env)
		//free_env(mini);
	//if (mini->token)
		//listfree(mini->token);
	//if (mini->args)
		//free_tab(mini->args);
	//if (mini->paths)
		//free_tab(mini->paths);
//}

//int	ft_latoi(const char *str)
//{
	//int				i;
	//int				j;
	//long long int	r;

	//i = 0;
	//j = 1;
	//r = 0;
	//while (str[i] == ' ' || str[i] == '\r' || str[i] == '\f'
		//|| str[i] == '\t' || str[i] == '\v' || str[i] == '\n')
		//i++;
	//if (str[i] == '-' || str[i] == '+')
	//{
		//if (str[i] == '-')
			//j = -1;
		//i++;
	//}
	//while (str[i] >= '0' && str[i] <= '9')
	//{
		//r = (r * 10) + (str[i] - '0');
		//i++;
	//}
	//return (r * j);
//}

//void	b_exit(t_shell *mini, t_token *list)
//{
	//char	*s;

	//perror("exit\n");
	//exit_until(mini);
	//if (!list->next)
		//exit(0);
	//else
	//{
		//list = list->next;
		//if (ft_latoi(list->s) > 2147483647)
		//{
			//s = ft_strjoin("minishell: exit: ", list->s);
			//exit(2);	
		//}
		//if (list->next)
		//{
			//perror("minishell: exit: too many argument\n");
			//exit(mini->rtn);
		//}
	//}

//}
