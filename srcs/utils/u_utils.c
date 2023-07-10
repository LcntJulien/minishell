/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:54 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/10 13:05:13 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*var_content(t_shell *mini, char *str)
{
	int		i;
	int		j;
	int		len;
	char	*s;

	i = 0;
	j = 0;
	if (*str)
	{
		len = ft_strlen(str);
		while (str[i] && str[i] != '=')
			i++;
		if (str[i] == '=')
			i++;
		s = ft_calloc(sizeof(char), (len - i + 1));
		if (!s)
			ft_exit_plus(mini, mini->token, 0);
		while (str[i] && i < len)
		{
			s[j] = str[i++];
			j++;
		}
		return (s);
	}
	return (NULL);
}

char	*return_var_content(t_shell *mini, char *var)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	while (mini->env[++i])
	{
		tmp = var_name(mini, mini->env[i]);
		len = ft_strlen(tmp);
		if (ft_strncmp(tmp, var, len) == 0)
		{
			free(tmp);
			tmp = NULL;
			return (var_content(mini, mini->env[i]));
		}
		free(tmp);
		tmp = NULL;
	}
	free(tmp);
	tmp = NULL;
	return (NULL);
}

char	*var_name(t_shell *mini, char *str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	if (*str)
	{
		while (str[i] && str[i] != '=')
			i++;
		s = ft_calloc(sizeof(char), (i + 1));
		if (!s)
			ft_exit_plus(mini, mini->token, 0);
		while (str[j] && j < i)
		{
			s[j] = str[j];
			j++;
		}
		return (s);
	}
	return (NULL);
}

char	*return_var_name(t_shell *mini, char *var)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	while (mini->env[++i])
	{
		tmp = var_name(mini, mini->env[i]);
		len = ft_strlen(tmp);
		if (ft_strncmp(tmp, var, len) == 0)
			return (tmp);
		free(tmp);
		tmp = NULL;
	}
	free(tmp);
	tmp = NULL;
	return (NULL);
}

int	existing_var(t_shell *mini, char *var)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	while (mini->env[++i])
	{
		tmp = var_name(mini, mini->env[i]);
		len = ft_strlen(tmp);
		if (ft_strncmp(tmp, var, len) == 0)
		{
			free(tmp);
			tmp = NULL;
			return (i);
		}
		free(tmp);
		tmp = NULL;
	}
	return (-1);
}
