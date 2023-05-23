/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:37:14 by jlecorne          #+#    #+#             */
/*   Updated: 2023/05/16 17:09:42 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		if (quote_state(mini->line, i) != 2 && mini->line[i] == '$' && i
			&& mini->line[i - 1] != '\\')
			nl[j++] = (char)(-mini->line[i++]);
		else if (quote_state(mini->line, i) == 0 && is_sep(mini->line, i))
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

void	parse(t_shell *mini)
{
	t_token	*token;
	char	*line;
	char	*tab[9];

	tab[0] = "CMD";
	tab[1] = "ARG";
	tab[2] = "VAR";
	tab[3] = "INPUT";
	tab[4] = "OUTPUT";
	tab[5] = "STRING";
	tab[6] = "APPEND";
	tab[7] = "HEREDOC";
	tab[8] = "PIPE";
	if (!mini->line[0])
		return ;
	else if (line_check(mini))
		return ;
	line = parse_line(mini);
	if (line && line[0] == '$')
		line[0] = (char)(-line[0]);
	mini->token = get_tokens(line);
	token = mini->token;
	while (token != NULL)
	{
		ft_putstr_fd(token->s, 1);
		ft_putstr_fd(" --> ", 1);
		ft_putendl_fd(tab[token->type], 1);
		token = token->next;
	}
	free(line);
}
