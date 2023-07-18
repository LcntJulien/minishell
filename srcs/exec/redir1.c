/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:57:43 by jlecorne          #+#    #+#             */
/*   Updated: 2023/07/18 02:32:16 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_handler(t_shell *mini, t_token *tk)
{
	char	**tab;
	char	**alloctab;
	char	*tmp;
	int		i;

	(void)mini;
	tab = ft_calloc(sizeof(char *), 20);
	alloctab = NULL;
	tmp = NULL;
	i = 0;
	while (1)
	{
		tmp = readline("\033[0;35m\033[▸ \033[");
		if (ft_strncmp(tmp, tk->s, ft_strlen(tmp)) == 0)
			break ;
		tab[i] = tmp;
		i++;
	}
	alloctab = malloc(sizeof(char *) * i + 1);
	if (!alloctab)
		return ;
	i = -1;
	while (tab[++i] != NULL)
		alloctab[i] = ft_strdup(tab[i]);
	alloctab[i] = NULL;
}

	// i = -1;
	// while (alloctab[++i] != NULL)
	// 	fprintf(stderr, "%s\n", alloctab[i]);

void	heredoc_manager(t_shell *mini)
{
	t_token *tk;

	tk = mini->token;
	while (tk->next != NULL)
	{
		if (tk->type == HEREDOC)
			heredoc_handler(mini, tk->next);
		tk = tk->next;
	}
}