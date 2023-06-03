/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/03 11:14:39 by jmathieu         ###   ########.fr       */
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

static void	swap_string(char **exp, int i, int j)
{
	char	*tmp;

	tmp = exp[i];
	exp[i] = ft_strdup(exp[j]);
	exp[j] = ft_strdup(tmp);
}

static void	sort_in_tab(char **exp, int line)
{
	int		i;
	int		j;
	int		len;
	
	j = 1;
    while (j < line)
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
	{
		exp[i] = ft_strdup(mini->env[i]);
		printf("%s\n", exp[i]);
	}
	exp[i] = NULL;
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
		if (content == 0)
			printf("declare -x %s", name);
		else
			printf("declare -x %s\"%s\"\n", name, content);
	}
	return (1);
}

static void print_listed_env(t_shell *mini)
{
	int		i;
	int		line;
	char	**exp;

	i = -1;
	line = tab_lines(mini->env);
	if (!line)
		ft_exit(mini, 1);
	exp = ft_calloc((line + 1), sizeof(char *));
	if (!exp)
		ft_exit(mini, 1);
	copy_tab(mini, exp);
	sleep(3);
	i = -1;
	while (exp[++i])
		printf("%s\n", exp[i]);
	sort_in_tab(exp, line);
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

void	b_export(t_shell *mini)
{
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
	print_listed_env(mini);
		//return ;
	//}
	//while (mini->env[++i])
	//{
 		//if (!strncmp(mini->env[i], mini->token->s, ft_strlen()))
 		//{
 			//replace_var(mini, sf, i, cpy);
 			//return ;
 		//}
	//}
	//add_var(mini, sf, cpy);
}
