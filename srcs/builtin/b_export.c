/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/17 17:16:34 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	newtab(t_shell *mini, int choice, char **cpy)
{
	int i;
	
	i = 0;
	while (mini->env[i])
		i++;	
	if (choice == 1)
		cpy = calloc((i + 2), sizeof(char *));
	else
		cpy = calloc((i + 1), sizeof(char *));
	if (!cpy)	
	{
		//gerer les leaks suppression tableaux etc...
		// et changer la sortie d'erreur et message.
		exit (0);
	}
}

static void	replace_var(t_shell *mini, char *str, int i, char **cpy)
{
	int	j;
	char *var;

	j = 0;
	newtab(mini, 0, cpy);
	while (mini->env[j] && j < i)
	{
		var = ft_strdup(mini->env[j]);
		cpy[j] = var;
		j++;
	}
	var = ft_strdup(str);	
	cpy[j] = var;
	while (mini->env[++j])
	{
		var = ft_strdup(mini->env[j]);
		cpy[j] = var;
	} 
	cpy[j] = "\0";
	j = -1;
	while (cpy[++j])
		mini->env[j] = cpy[j];
	mini->env[j] = "\0";
}

void static	add_var(t_shell *mini, char *str, char **cpy)
{
	int	j;
	char *var;

	j = -1;
	newtab(mini, 1, cpy);
	while (mini->env[++j])
	{
		var = ft_strdup(mini->env[j]);
		cpy[j] = var;
	} 
	var = ft_strdup(str);	
	cpy[j] = var;
	cpy[++j] = "\0";	
	j = -1;
	while (cpy[++j])
		mini->env[j] = cpy[j];
	mini->env[j] = "\0";
}

void	b_export(t_shell *mini, char *str)
{
	int		i;
	int		len;
	char	**cpy;
	char	*strf;

	i = -1;
	len = 0;
	cpy = NULL;
	while (str[++i] != '=')
		len++;
	i = -1;
	strf = format_string(str);
	while (mini->env[++i])
	{
		if (!strncmp(mini->env[i], str, len - 1))
		{
			replace_var(mini, strf, i, cpy);
			return ;
		}
	}
	add_var(mini, strf, cpy);
}
