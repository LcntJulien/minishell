/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:20 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/16 12:22:02 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	args_to_print(t_token *list)
{
	int		nb_args;
	t_token	*tmp;

	tmp = list;
	nb_args = 0;
	while (tmp  && ((tmp->type >= 0 && tmp->type <= 5)))
	{
			nb_args++;
			tmp = tmp->next;
	}
	return (nb_args);
}

static int	valid_option(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] != '-')
		return (0);
	else
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] && str[i] != ' ')
			return (0);
		else
			return (1);
	}
}

static int	nb_option(t_token *list)
{
	int		nb_opt;

	nb_opt = 0;
	while (list && list->type == 3)
	{
		if (!valid_option(list->s))
			break ;
		nb_opt++;
		list = list->next;
	}
	return (nb_opt);
}

static void	print_echo(t_shell *mini, t_token *list, int nb_args)
{
	int	nb_opt;

	nb_opt = nb_option(mini->token->next);
	while (nb_args > 0)
	{
		printf("%s", list->s);
		mini->rtn = 0;
		nb_args--;
		if (list->next && nb_args > 0)
			printf(" ");
		else
			break ;
		list = list->next;
	}
	if (nb_opt == 0)
		printf("\n");
}

void	b_echo(t_shell *mini, t_token *list)
{
	int		nb_args;
	int		nb_opt;
	
	if (!mini->token->next)
	{
		mini->rtn = 0;
		return ;
	}
	else
	{
		mini->rtn = 0;
		list = mini->token->next;
		nb_opt = nb_option(list);
		if (!list)
			return ;
		while (list && nb_opt > 0)
		{
			nb_opt--;
			list = list->next;
		}
		if (!list)
			return ;
		nb_args = args_to_print(list);
		print_echo(mini, list, nb_args);
	}
}
