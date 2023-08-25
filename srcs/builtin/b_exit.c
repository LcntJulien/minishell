/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:26 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/24 08:00:33y jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	check_condition_exit(t_shell *mini, unsigned long ul)
{
	if (ul > 9223372036854775807)
		exit_too_much(mini);
}

static long long	ft_latoi(const char *str, t_shell *mini)
{
	int					i;
	int					sign;
	unsigned long long	ul;

	i = 0;
	sign = 1;
	ul = 0;
	while (str[i] == ' ' || str[i] == '\r' || str[i] == '\f'
		|| str[i] == '\t' || str[i] == '\v' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ul = (ul * 10) + (str[i] - '0');
		i++;
	}
	check_condition_exit(mini, ul);
	return ((long long)ul * sign);
}

static void is_it_a_char(t_shell *mini)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = mini->token->next;
	if (tmp)
	{
		if (tmp->s[i] && (tmp->s[i] == '-'
				|| tmp->s[i] == '+'))
			i++;
		while (tmp->s[i])	
		{
			if (ft_isdigit(tmp->s[i]))
				i++;
			else
			{
				ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
				ft_putstr_fd(tmp->s, STDERR_FILENO);
				ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
				exit_until(mini);
				exit(255);
			}
		}
	}
}

void	b_exit(t_shell *mini, t_token *list)
{
	long long	nb;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (list->next)
	{
		list = list->next;
		is_it_a_char(mini);
		nb = ft_latoi(list->s, mini);
		if (list->next)
			ft_putstr_fd("minishell: exit: too many arguments\n",
				STDERR_FILENO);
		mini->rtn = nb % 256;
		exit_until(mini);
		exit(mini->rtn);
	}
	exit_until(mini);
	exit(mini->rtn);
}
