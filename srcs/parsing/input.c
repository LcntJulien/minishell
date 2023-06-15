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

/*
 NOTES:
 - Le parsing doit pouvoir gérer `'e''c''h''o'` ou tout autre fonction correcte
 sans quotes ouverts
 - Les variables valides entre quotes doivent aussi prendre leur valeur
 en content
*/

int	parse_err_msg(t_shell *mini, t_token *tk, int status)
{
	char	*tab[255];

	tab[2] = "; syntax error near unexpected token";
	tab[127] = "; command not found";
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tk->s, 2);
	ft_putendl_fd(tab[status], 2);
	mini->rtn = status;
	free(mini->line);
	return (1);
}

int	parse_err(t_shell *mini, t_token *tk)
{
	while (tk)
	{
		if (quote_state(tk->s, ft_strlen(tk->s)) || (tk->type == VAR
					&& (!tk->prev || tk->prev->type == PIPE)))
			return (parse_err_msg(mini, tk, 127));
		else if (tk->type == PIPE && !tk->next)
			return (parse_err_msg(mini, tk, 2));
		tk = tk->next;
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
	return (nl);
}

void	parse(t_shell *mini)
{
	t_token	*token;
	char	*line;

	if (!mini->line[0])
		return ;
	line = parse_line(mini);
	mini->token = get_tokens(line);
	token = mini->token;
	while (token)
	{
		if (token->type <= VAR)
			post_tk_type(token, mini);
		token = token->next;
	}
	token = mini->token;
	if (parse_err(mini, token))
		return ;
	clean_tokens(token);
	display_tokens(token);
	free(line);
	free(mini->line);
}
