/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:26 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/18 16:16:00 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

long long	ft_latoi(const char *str)
{
	int				i;
	int				j;
	long long		r;

	i = 0;
	j = 1;
	r = 0;
	while (str[i] == ' ' || str[i] == '\r' || str[i] == '\f'
		|| str[i] == '\t' || str[i] == '\v' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + (str[i] - '0');
		i++;
	}
	return (r * j);
}

void	exit_until(t_shell *mini)
{
	if (mini->home)
		free_str(mini->home);
	if (mini->env)
		free_env(mini);
	if (mini->token)
		free_token(mini, mini->token);
	if (mini->args)
		free_tab(mini->args);
	if (mini->paths)
		free_tab(mini->paths);
}

void	exit_too_many(void)
{
}

void	exit_too_much(t_shell *mini)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin("minishell: exit: ", mini->token->s);
	s2 = ft_strjoin(s1, ": numeric argument required\n");
	free_str(s1);
	perror(s2);
	free_str(s2);
	exit_until(mini);
	exit(255);
}

void	b_exit(t_shell *mini, t_token *list)
{
	double	nb;
	
	perror("exit\n");
	if (list->next)
	{
		list = list->next;
		nb = ft_latoi(list->s);
		if (nb < -9223372036854775807 || nb > 9223372036854775807)
			exit_too_much(mini);
		else if (list->next)
			perror("minishell: exit: too many argument\n");
		mini->rtn = (long)nb % 256;
		exit_until(mini);
		exit(mini->rtn);
	}
	exit_until(mini);
	exit(0);
}
