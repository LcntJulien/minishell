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

void	parse_err(t_shell *mini)
{
	t_token	*tk;

	tk = mini->token;
	while (tk)
	{
		if (tk->type == PIPE && !tk->next)
			err_manager(mini, tk, 3);
		tk = tk->next;
	}
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
	if (!nl)
		ft_exit(mini, 2);
	while (mini->line[i])
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
	if (!mini->token)
		ft_exit(mini, 3);
	token = mini->token;
	clean_tokens(token);
	while (token)
	{
		if (token->type <= VAR)
			post_tk_type(token, mini);
		token = token->next;
	}
	free(line);
	parse_err(mini);
}
