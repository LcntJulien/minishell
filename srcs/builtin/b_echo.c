/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:20 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/29 08:11:27 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	search_options(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if (!inside_quotes(str) && str[++i] != '-')
		return (0);
	while (str[++i] && str[i] < len)
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

//static void	echo_no_redir_with_opt(t_token *list)
//{
	/* a coder, voir comment se comporte le promt et modifier eventuellement */
//}

static void	echo_no_redir_without_opt(t_shell *mini)
{
	int	q;
	int	r;

	q = 0;
	while (mini->token)
	{
		q = inside_quotes(mini->token->s);
		if (q == 0)
			r = without_quote_print(mini->token->s, mini);
		else if (q == 1)
			r = with_squote_print(mini->token->s, mini);
		else if (q == 2)
			r = with_dquote_print(mini->token->s, mini);
		mini->token = mini->token->next;
		if (mini->token && r != 0)
			printf(" ");
	}
}

static void	define_echo_args(t_shell *mini)
{
	t_token	*opt;
	int		i;

	i = 0;
	opt = mini->token;
	while (opt && search_options(opt->s))
	{
		i++;
		opt = opt->next;
	}
	//if (i != 0)
		//echo_no_redir_with_opt(opt);
	//else
	echo_no_redir_without_opt(mini);
}

void	b_echo(t_shell *mini)
{
	t_token	*list;
	int		i;

	list = mini->token;
	i  = nb_args_no_redir(list);
	if (i != 0)
		define_echo_args(mini);
	/* si on a besoin d'ecrire le retour avant de sortir*/
	//else
	//{
		//printf("\n");
		//return ;
	//}

	/* est-ce qu'il faut free ici ou plus en amont ?*/
	return ;
}
