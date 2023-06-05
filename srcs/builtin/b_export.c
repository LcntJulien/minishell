/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/05 09:28:42 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_existing_args(t_shell *mini, char *s)
{
	int	i;
	int len;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], var_name(s), ft_strlen(var_name(s))))
			i++;
		else
			return (1);
	}
	return (0);
}

static int	alpha_num_underscore(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
	{	
		if ((s[i] >= '0' && s[i] >= '9')
		|| (s[i] >= 'A' && s[i] >= 'Z')
		|| (s[i] >= 'a' && s[i] >= 'z')
		|| s[i] == '_')
			i++;
		else
			return (0);
	}
	if (s[i] == '=')
		return (1);
	return (0);
}

static int	check_valid_args(t_shell *mini, int nb)
{
	t_token	*tmp;
	int		valid;

	valid = nb;
	tmp = mini->token->next;
	while (nb > 0)
	{
		if (!alpha_num_underscore(tmp->s))
			valid --;
		else
		{
			if (check_existing_args(mini, tmp->s))
				valid--;
		}
		nb--;
		tmp = tmp->next;
	}
	return (valid);
}

void	b_export_arg(t_shell *mini)
{
	int		i;
	int		nb_args;
	int		lines;

	i = -1;
	nb_args = check_valid_args(mini, check_nb_args(mini, 1));
	if (nb_args <= 0)
		return ;
		// failed option to build
	lines = nb_args + tab_lines(mini->env);
	mini->env = renew_env(mini, lines, nb_args);
	//while (mini->env[++i])
	//{
 		//if (!strncmp(mini->env[i], mini->token->s, ft_strlen(test)))
 		//{
 			//replace_var(mini, sf, i, cpy);
 			//return ;
 		//}
	//}
	//add_var(mini, sf, cpy);
}

void	b_export(t_shell *mini)
{
	if (!mini->token->next)
		print_listed_env(mini);
	else
	{
		b_export_arg(mini);
	}
}
