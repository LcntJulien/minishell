/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:20 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/27 11:57:56 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	search_options(char *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (!inside_quotes(str) && str[++i] != "-")
		return (0);
	while (str[++i] && str[i] < len)
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

static void	define_echo_args(t_shell *mini)
{
	t_token	*opt;
	int		i;

	i = 0;
	opt = mini->token;
	while (opt && search_options(opt->s, 'n'))
	{
		i++;
		opt = opt->next;
	}
	if (i != 0)
		echo_no_redir_with_opt(opt);
	else
		echo_no_redir_without_opt(mini);
}

static void	echo_no_redir_with_opt(t_token *list)
{
	/* a coder, voir comment se comporte le promt et modifier eventuellement */
}

static void	echo_no_redir_without_opt(t_shell *mini)
{
	int		q;

	q = 0;
	while (mini->token)
	{
		q = inside_quotes(mini->token->s);
		if (q == 0)
			b_print_arg(mini->token->s, 1);
		else if (q == 1)
			b_print_arg(mini->token->s, 1);
		else if (q == 2)
			b_print_arg(mini->token->s, 2);
		mini->token = mini->token->next;
		if (mini->token)
			printf(" ");
	}
}

void	b_echo(t_shell *mini)
{
	t_token	*list;
	int		i;

	i = 0;
	list = mini->token;
	if (!nb_args_no_redir(list, &i))
	{
		printf("\n");
		return ;
	}
	else
	{
		list = list->next;
		define_echo_args(mini);
	}
	/* est-ce qu'il faut free ici ou plus en amont ?*/
	return ;
}
