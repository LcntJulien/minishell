/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:08:47 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/02 19:58:32 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_vname(char *s, int idx)
{
	char	*var;
	int		len;
	int		i;

	var = NULL;
	len = 0;
	i = idx;
	while (s[++i])
	{
		if (!s[i] || s[i] == ' ' || s[i] == '\'' || s[i] == '\"' || s[i] == '$')
			break ;
		len++;
	}
	var = ft_substr(s, (idx + 1), len);
	return (var);
}

char	*get_nvar(t_shell *mini, char *vname)
{
	char	*tmp;
	char	*nvar;
	int		i;

	tmp = ft_calloc(sizeof(char), ft_strlen(vname) + 2);
	nvar = NULL;
	i = -1;
	while (vname[++i])
		tmp[i] = vname[i];
	tmp[i] = '=';
	i = -1;
	if (mini->env)
	{
		while (mini->env[++i])
		{
			if (ft_strncmp(tmp, mini->env[i], ft_strlen(tmp)) == 0)
			{
				nvar = ft_substr(mini->env[i], (ft_strlen(vname) + 1),
						ft_strlen(mini->env[i]) - (ft_strlen(vname) + 1));
			}
		}
	}
	free(tmp);
	return (nvar);
}

int	valid_var(t_shell *mini, char *s)
{
	char	*tmp;
	int		i;

	tmp = ft_calloc(sizeof(char), ft_strlen(s) + 2);
	i = -1;
	while (s[++i])
		tmp[i] = s[i];
	tmp[i] = '=';
	i = -1;
	if (mini->env)
	{
		while (mini->env[++i])
			if (ft_strncmp(tmp, mini->env[i], (ft_strlen(tmp) - 1)) == 0)
			{
				free(tmp);
				return (1);
			}
	}
	free(tmp);
	return (0);
}

char	*rewrite(t_shell *mini, char *s, char *vname, int idx)
{
	char	*nvar;
	char	*ns;
	int		i;
	int		j;

	nvar = get_nvar(mini, vname);
	ns = NULL;
	i = idx;
	j = -1;
	while (s[++i] && s[i] != ' ' && s[i] != '\'' && s[i] != '\"' && s[i] != '$')
		;
	i -= idx;
	ns = ft_calloc(sizeof(char), ((ft_strlen(s) + ft_strlen(nvar)) - i) + 1);
	i = -1;
	while (s[++i] && i != idx)
		ns[i] = s[i];
	while (nvar[++j])
		ns[i + j] = nvar[j];
	j += i;
	while (s[++i] && s[i] != ' ' && s[i] != '\'' && s[i] != '\"' && s[i] != '$')
		;
	while (s[i])
		ns[j++] = s[i++];
	free(nvar);
	return (ns);
}

void	convert_var(t_shell *mini, t_token *tk)
{
	char	*cur;
	int		i;

	cur = NULL;
	i = -1;
	while (tk->s[++i])
	{
		if (tk->s[i] == '$')
		{
			cur = get_vname(tk->s, i);
			if (valid_var(mini, cur))
			{
				tk->s = rewrite(mini, tk->s, cur, i);
				i = -1;
			}
		}
	}
	if (cur)
		free(cur);
}

int	contain_var(t_shell *mini, t_token *tk)
{
	char	*s;
	int		i;
	int		j;

	s = NULL;
	i = -1;
	while (tk->s[++i])
	{
		if (tk->s[i] == '$')
		{
			j = i + 1;
			while (tk->s[j] && tk->s[j] != ' ' && tk->s[j] != '\''
				&& tk->s[j] != '\"' && tk->s[j] != '$')
				j++;
			s = ft_substr(tk->s, (i + 1), j - i);
			if (valid_var(mini, s))
			{
				free(s);
				return (1);
			}
		}
	}
	if (s)
		free(s);
	return (0);
}
