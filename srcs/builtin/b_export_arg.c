/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/03 23:16:21 by jmathieu         ###   ########.fr       */
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

//void	b_export_arg(t_shell *mini)
//{
	//int		i;
	//int		len;
	//char	**cpy;
	//char	*sf;

	//i = -1;
	//len = 0;
	//cpy = NULL;
	//sf = NULL;
	//i = -1;
	//if (!mini->token->next)
	//{
	//while (mini->env[++i])
	//{
 		//if (!strncmp(mini->env[i], mini->token->s, ft_strlen()))
 		//{
 			//replace_var(mini, sf, i, cpy);
 			//return ;
 		//}
	//}
	//add_var(mini, sf, cpy);
//}
