/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/05 18:48:45 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	swap_string(char **exp, int i, int j)
{
	char	*tmp;

	tmp = exp[i];
	exp[i] = ft_strdup(exp[j]);
	exp[j] = ft_strdup(tmp);
}

static void	sort_in_tab(char **exp, int lines)
{
	int		i;
	int		j;
	int		len;
	
	j = 1;
    while (j < lines)
	{
        i = 0;
        while (i < j)
		{
			if (ft_strlen(exp[i]) >= ft_strlen(exp[j]))
				len = ft_strlen(exp[i]);
			else
				len = ft_strlen(exp[j]);
			if (ft_strncmp(exp[i], exp[j], len) > 0)
			{
				swap_string(exp, i, j);
				i = 0;
			}
            else
				i++;
        }
        j++;
    }
}

static void	copy_tab(t_shell *mini, char **exp)
{
	int		i;

	i = -1;
	while (mini->env[++i])
		exp[i] = ft_strdup(mini->env[i]);
}

static int	print_export(char **exp)
{
	int		i;
	char	*name;
	char	*content;

	i = -1;
	while (exp[++i])
	{	
		name = var_name(exp[i]);
		if (!name)
			return (0);
		content = var_content(exp[i]);
		if (content[0] == 0)
			printf("declare -x %s\n", name);
		else
			printf("declare -x %s=\"%s\"\n", name, content);
	}
	return (1);
}

void print_listed_env(t_shell *mini)
{
	int		i;
	int		lines;
	char	**exp;

	lines = tab_lines(mini->env);
	if (!lines)
		ft_exit(mini, 1);
	exp = ft_calloc((lines + 1), sizeof(char *));
	if (!exp)
		ft_exit(mini, 1);
	copy_tab(mini, exp);
	sort_in_tab(exp, lines);
	if (!print_export(exp))
		ft_exit(mini, 1);
	i = -1;
	while (exp[++i])
	{
		free(exp[i]);
		exp[i] = NULL;
	}
	free(exp);
}
