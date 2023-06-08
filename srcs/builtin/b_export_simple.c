/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/08 15:22:30 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_var_export(char *name, char *content)
{
	free(name);
	name = NULL;
	free(content);
	content = NULL;
}

static void print_export(t_shell *mini, char **exp)
{
	int		i;
	char	*name;
	char	*content;

	i=-1;
	while (exp[++i])
	{	
		name = var_name(mini, exp[i]);
		content = var_content(mini, exp[i]);
		if (!is_there_an_equal(exp[i]))
			printf("declare -x %s\n", name);
		else
			printf("declare -x %s=\"%s\"\n", name, content);
		free_var_export(name, content);
	}
}

static void	sort_in_tab(char **exp, int lines)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;
	
	j = 1;
    while (j < lines)
	{
        i = 0;
        while (i < j)
		{
			len = max_len(ft_strlen(exp[i]), ft_strlen(exp[j]));
			if (ft_strncmp(exp[i], exp[j], len) > 0)
			{
				tmp = exp[i];
				exp[i] = exp[j];
				exp[j] = tmp;
			}
            else
				i++;
        }
        j++;
    }
}

static void	copy_tab(t_shell *mini, char **exp, int lines)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < lines)
	{
		if (ft_strncmp(mini->env[i], "_=env", 5))
		{
			exp[j] = mini->env[i];
			j++;
		}
		i++;
	}
	exp[j] = 0;
}

void print_listed_env(t_shell *mini)
{
	int		lines;
	char	**exp;

	lines = tab_lines(mini->env) - 1;
	printf("Lines = %d\n", lines);
	if (!lines)
		ft_exit(mini, 1);
	exp = ft_calloc((lines + 1), sizeof(char *));
	if (!exp)
		ft_exit(mini, 1);
	copy_tab(mini, exp, lines);
	sort_in_tab(exp, lines);
	print_export(mini, exp);
	mini->rtn = 1;
	free_tab(exp);
}
