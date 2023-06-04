/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/04 11:25:41 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//static void	newtab(t_shell *mini, int choice, char **cpy)
//{
	//int	i;

	//i = 0;
	//while (mini->env[i])
 		//i++;
	//if (choice == 1)
 		//cpy = calloc((i + 2), sizeof(char *));
	//else
 		//cpy = calloc((i + 1), sizeof(char *));
	//if (!cpy)
 		//exit (0);
//}

//static void	replace_var(t_shell *mini, char *s, int i, char **cpy)
//{
	//int		j;
	//char	*var;

	//j = 0;
	//newtab(mini, 0, cpy);
	//while (mini->env[j] && j < i)
	//{
 		//var = ft_strdup(mini->env[j]);
 		//cpy[j] = var;
 		//j++;
	//}
	//var = ft_strdup(s);
	//cpy[j] = var;
	//while (mini->env[++j])
	//{
 		//var = ft_strdup(mini->env[j]);
 		//cpy[j] = var;
	//}
	//cpy[j] = "\0";
	//j = -1;
	//while (cpy[++j])
 		//mini->env[j] = cpy[j];
	//mini->env[j] = "\0";
	//}

//static void	add_var(t_shell *mini, char *s, char **cpy)
//{
	//int		j;
	//char	*var;

	//j = -1;
	//newtab(mini, 1, cpy);
	//while (mini->env[++j])
	//{
 		//var = ft_strdup(mini->env[j]);
 		//cpy[j] = var;
	//}
	//var = ft_strdup(s);
	//cpy[j] = var;
	//cpy[++j] = "\0";
	//j = -1;
	//while (cpy[++j])
 		//mini->env[j] = cpy[j];
	//mini->env[j] = "\0";
//}

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

static int	check_nb_args(t_shell *mini)
{
	t_token	*tmp;
	int		nb;

	nb = 0;
	tmp = mini->token;
	while (tmp->next && tmp->next->type == ARG)
	{
		nb++;
		tmp = tmp->next;
	}
	return (nb);
}

void	b_export_arg(t_shell *mini)
{
	int		i;
	int		nb_args;
	int		lines;

	i = -1;
	nb_args = check_valid_args(mini, check_nb_args(mini));
	if (nb_args <= 0)
		return ;
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
