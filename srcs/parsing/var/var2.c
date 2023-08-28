/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:56:10 by jmathieu          #+#    #+#             */
/*   Updated: 2023/08/28 15:03:54 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../include/minishell.h"

char	*other_variable(t_shell *mini, t_token *tk, int i)
{
	char	*new_var;

	new_var = NULL;
	if (tk->s[i] == '$')
		new_var = ft_strdup(ft_itoa(getpid()));
	else if (tk->s[i] == '_')
		new_var = return_var_content(mini, "_");
	else
		new_var = ft_strdup(ft_itoa(mini->rtn));
	return (new_var);
}

char	*get_other_var(char *vname)
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
	free(tmp);
	return (nvar);
}

char	*get_os(char *s, char *nvar, int idx, int vname_len)
{
	char	*ns;
	int		i;
	int		j;

	ns = NULL;
	i = -1;
	j = -1;
	if ((ft_strlen(s) + ft_strlen(nvar) - vname_len) == 0)
		return (NULL);
	ns = ft_calloc(sizeof(char), ((ft_strlen(s) + ft_strlen(nvar)) - vname_len)
			+ 1);
	while (s[++i] && i != idx)
		ns[i] = s[i];
	while (nvar && nvar[++j])
		ns[i + j] = nvar[j];
	if (!nvar)
		j++;
	j += i;
	while (s[++i] && s[i] != ' ' && s[i] != '\'' && s[i] != '\"' && s[i] != '$')
		;
	while (s[i])
		ns[j++] = s[i++];
	return (ns);
}

char	*rewrite2(t_shell *mini, char *s, char *iter, int idx)
{
	char	*ns;
	int		i;

	ns = NULL;
	i = idx;
	(void)mini;
	while (s[++i] && s[i] != ' ' && s[i] != '\'' && s[i] != '\"' && s[i] != '$')
		;
	i -= idx;
	ns = get_os(s, iter, idx, i);
	return (ns);
}
