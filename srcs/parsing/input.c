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

void	parse_var(t_shell *mini)
{
	t_token	*cp;

	cp = mini->token;
	while (cp)
	{
		if (contain_var(cp->s))
			convert_var(mini, cp);
		cp = cp->next;
	}
}

char	*line_alloc(t_shell *mini)
{
	char	*nl;
	int		sep;
	int		i;

	nl = NULL;
	sep = 0;
	i = -1;
	while (mini->line[++i])
		if (is_sep(mini->line, i) && !is_sep(mini->line, i + 1))
			sep++;
	nl = ft_calloc(sizeof(char), (2 * sep + i + 1));
	return (nl);
}

char	*parse_line(t_shell *mini)
{
	char	*nl;
	int		i;
	int		j;

	nl = line_alloc(mini);
	i = 0;
	j = 0;
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
	return (nl);
}

void	parse_input(t_shell *mini)
{
	t_token	*token;
	char	*line;

	if (!mini->line)
		return ;
	line = parse_line(mini);
	mini->token = get_token(line);
	token_idx(mini);
	parse_var(mini);
	if (syntax_check(mini))
		return ;
	token = mini->token;
	clean_tokens(token);
	while (token)
	{
		if (token->type <= VAR)
			post_tk_type(token);
		token = token->next;
	}
	free(line);
	mini->ncmd = nb_cmd(mini);
}
