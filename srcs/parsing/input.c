/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:52:33 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/24 17:23:40 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	parse_err(t_shell *mini, t_token *tk, int err)
{
	ft_putstr_fd("minishell: ", 2);
	if (!err)
	{
		ft_putstr_fd(tk->s, 2);
		ft_putendl_fd(": syntax error", 2);
		mini->rtn = 2;
	}
	else
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putstr_fd(tk->s, 2);
		ft_putendl_fd("'", 2);
		mini->rtn = 258;
	}
	return (1);
}

char	*alloc_line(t_shell *mini)
{
	char	*nl;
	int		i;
	int		sep;

	i = 0;
	sep = 0;
	while (mini->line[i])
	{
		if (is_sep(mini->line, i) && !is_sep(mini->line, i + 1))
			sep++;
		i++;
	}
	nl = malloc(sizeof(char) * (2 * sep + i + 1));
	if (!nl)
		return (NULL);
	return (nl);
}

char	*parse_line(t_shell *mini)
{
	char	*nl;
	int		i;
	int		j;

	i = 0;
	j = 0;
	nl = alloc_line(mini);
	while (mini->line[i])
	{
		if (quote_state(mini->line, i) == 0 && is_sep(mini->line, i))
		{
			nl[j++] = ' ';
			nl[j++] = mini->line[i++];
			if (quote_state(mini->line, i) == 0 && (mini->line[i] == '>'
					|| mini->line[i] == '<'))
				nl[j++] = mini->line[i++];
			nl[j++] = ' ';
		}
		else
			nl[j++] = mini->line[i++];
	}
	nl[j] = '\0';
	return (nl);
}

void	parse(t_shell *mini)
{
	t_token	*token;
	char	*line;

	if (!mini->line)
		return ;
	line = parse_line(mini);
	mini->token = get_tokens(line);
	token = mini->token;
	token_idx(mini);
	if (syntax_check(mini, 0))
		return ;
	clean_tokens(token);
	if (syntax_check(mini, 1))
		return ;
	while (token)
	{
		if (token->type <= VAR)
			post_tk_type(token, mini);
		token = token->next;
	}
	free(line);
}
