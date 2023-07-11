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

void	parse_err_msg(t_shell *mini, t_token *tk, int status)
{
	char	*msg;

	msg = "; syntax error near unexpected token";
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tk->s, 2);
	ft_putendl_fd(msg, 2);
	mini->rtn = status;
	free(mini->line);
	exit(status);
}

void	parse_err(t_shell *mini, t_token *tk)
{
	while (tk)
	{
		if (tk->type == PIPE && !tk->next)
			return (parse_err_msg(mini, tk, 2));
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
	token = mini->token;
	parse_err(mini, token);
	free(line);
	free(mini->line);
}
