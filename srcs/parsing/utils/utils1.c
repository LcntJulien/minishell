/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:27:35 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/14 23:53:33 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_sep(char *s, int i)
{
	if (ft_strchr("<>|", s[i]) && quote_state(s, i) == 0)
		return (1);
	else
		return (0);
}

int	is_quote(char *s)
{
	int	i;
	int	r;

	i = -1;
	r = 0;
	while (s && s[++i])
		if (s[i] == '\'' || s[i] == '\"')
			r++;
	return (r);
}

int	quote_state(char *s, int idx)
{
	int	quote;
	int	i;

	quote = 0;
	i = -1;
	while (s && s[++i] && i <= idx)
	{
		if (quote == 0 && s[i] == '\'')
			quote = 1;
		else if (quote == 0 && s[i] == '\"')
			quote = 2;
		else if (quote == 1 && s[i] == '\'')
			quote = 0;
		else if (quote == 2 && s[i] == '\"')
			quote = 0;
	}
	return (quote);
}

void	display_tokens(t_token *token)
{
	t_token	*cp;
	char	*tab[11];

	cp = token;
	while (cp && cp->prev && cp->prev->type != PIPE)
		cp = cp->prev;
	tab[0] = "CMD";
	tab[1] = "ARG";
	tab[2] = "VAR";
	tab[3] = "OPTION";
	tab[4] = "BUILTIN";
	tab[5] = "DECLAVAR";
	tab[6] = "PIPE";
	tab[7] = "INPUT";
	tab[8] = "OUTPUT";
	tab[9] = "APPEND";
	tab[10] = "HEREDOC";
	while (cp)
	{
		if (cp->s != NULL)
			fprintf(stderr, "%s -> %s -> %d\n", cp->s, tab[cp->type], cp->idx);
		else
			fprintf(stderr, "|VIDE| -> %s\n", tab[cp->type]);
		cp = cp->next;
	}
}
