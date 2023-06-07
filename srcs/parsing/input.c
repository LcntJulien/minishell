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
	char	*tab[11];

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
	while (token)
	{
		fprintf(stdout, "%s --> %s\n", token->s, tab[token->type]);
		token = token->next;
	}
}

int	line_check(t_shell *mini)
{
	if (quote_state(mini->line, ft_strlen(mini->line)))
	{
		ft_putendl_fd("minishell: syntax error: open quote", 2);
		mini->rtn = 2;
		free(mini->line);
		return (1);
	}
	return (0);
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
		if (is_sep(mini->line, i))
			sep++;
		i++;
	}
	if (!(nl = malloc(sizeof(char) * (2 * sep + i + 1))))
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
	while (nl && mini->line[i])
	{
		if (quote_state(mini->line, i) == 0 && is_sep(mini->line, i))
		{
			nl[j++] = ' ';
			nl[j++] = mini->line[i++];
			if (quote_state(mini->line, i) == 0 && mini->line[i] == '>')
				nl[j++] = mini->line[i++];
			nl[j++] = ' ';
		}
		else
			nl[j++] = mini->line[i++];
	}
	nl[j] = '\0';
	free(mini->line);
	return (nl);
}

void	parse(t_shell *mini)
{
	t_token	*token;
	char	*line;

	if (!mini->line[0])
		return ;
	else if (line_check(mini))
		return ;
	line = parse_line(mini);
	mini->token = get_tokens(line);
	token = mini->token;
	while (token)
	{
		if (token->type <= ARG)
			post_tk_type(token, mini);
		token = token->next;
	}
	token = mini->token;
	clean_tokens(token);
	display_tokens(token);
	free(line);
}
