/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:29:25 by jlecorne          #+#    #+#             */
/*   Updated: 2023/06/06 17:58:14 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *s)
{
	char	*tab[7];
	char	*cpy;
	int		i;

	tab[0] = "echo";
	tab[1] = "cd";
	tab[2] = "pwd";
	tab[3] = "export";
	tab[4] = "unset";
	tab[5] = "env";
	tab[6] = "exit";
	cpy = s;
	i = 0;
	if (s[0] == '\"' || s[0] == '\'')
		cpy = ft_substr(s, 1, ft_strlen(cpy) - 2);
	while (i <= 6)
	{
		if (ft_strncmp(tab[i], cpy, ft_strlen(cpy)) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_decla(char *s)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (s[i])
	{
		if (ft_strchr("=", s[i]))
			r++;
		i++;
	}
	return (r);
}

int	is_sep(char *line, int i)
{
	if (ft_strchr("<>|", line[i]) && quote_state(line, i) == 0)
		return (1);
	else
		return (0);
}

void	post_tk_type(t_token *tk, t_shell *mini)
{
	(void)mini;
	if (tk->type == CMD)
	{
		if (is_builtin(tk->s))
			tk->type = BUILTIN;
		else if (is_decla(tk->s))
			tk->type = DECLAVAR;
	}
	else if (tk->type == ARG)
	{
		if ((tk->s[0] == '\"' && tk->s[1] == '$') || tk->s[0] == '$')
		{
			tk->type = VAR;
			// convert_var(tk, mini);
		}
		else if (((tk->s[0] == '\"' || tk->s[0] == '\'') && tk->s[1] == '-')
						|| tk->s[0] == '-')
			tk->type = OPTION;
	}
}

void	tk_type(t_token *token)
{
	if (token->s[0] == '$')
		token->type = VAR;
	else if (ft_strncmp(token->s, "|", ft_strlen(token->s)) == 0)
		token->type = PIPE;
	else if (ft_strncmp(token->s, "<", ft_strlen(token->s)) == 0)
		token->type = INPUT;
	else if (ft_strncmp(token->s, ">", ft_strlen(token->s)) == 0)
		token->type = OUTPUT;
	else if (ft_strncmp(token->s, ">>", ft_strlen(token->s)) == 0)
		token->type = APPEND;
	else if (ft_strncmp(token->s, "<<", ft_strlen(token->s)) == 0)
		token->type = HEREDOC;
	else if (token->prev == NULL || token->prev->type == PIPE
			|| (token->prev->prev && token->prev->prev->type >= INPUT))
		token->type = CMD;
	else
		token->type = ARG;
}