/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hrdc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:57:43 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/29 18:29:31 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// void	ctrl_d_hrdc(t_shell *mini, int idx)
// {
// 	t_hrdc	*cp;
// 	t_hrdc	*tmp;
// 	int		i;

// 	cp = mini->hrdc;
// 	tmp = NULL;
// 	i = -1;
// 	while (cp->idx != idx)
// 		cp = cp->next;
// 	while (cp->content[++i])
// 		ft_putstr_fd(cp->content[i], 1);
// 	free_tab(cp->content);
// 	tmp = cp->next;
// 	free(cp);
// 	cp = tmp;
// }

// void	hrdc_filler(t_shell *mini, t_hrdc *hrdc, char **tab, int size)
// {
// 	int i;

// 	i = -1;
// 	hrdc->content = ft_calloc(sizeof(char *), (size + 1));
// 	if (!hrdc->content)
// 		err_manager(mini, NULL, 3);
// 	while (tab[++i] != NULL)
// 		hrdc->content[i] = ft_strdup(tab[i]);
// }

// void	add_hrdc(t_shell *mini, t_hrdc *hrdc)
// {
// 	t_hrdc	*cp;

// 	cp = mini->hrdc;
// 	if (cp == NULL)
// 		mini->hrdc = hrdc;
// 	else
// 	{
// 		while (cp->next != NULL)
// 			cp = cp->next;
// 		cp->next = hrdc;
// 	}
// }

// t_hrdc	*new_hrdc(t_token *tk)
// {
// 	t_hrdc	*hrdc;

// 	hrdc = malloc(sizeof(t_hrdc));
// 	if (!hrdc)
// 		return (NULL);
// 	hrdc->idx = tk->idx;
// 	hrdc->content = NULL;
// 	hrdc->next = NULL;
// 	return (hrdc);
// }

void	heredoc_handler(t_shell *mini, t_token *tk, int i)
{
	char	*tmp;

	tmp = NULL;
	g_sig = 2;
	while (1)
	{
		tmp = readline("\033[0;35m\033[1m▸ \033[0m");
		if (!tmp || (tmp && tmp[0] && ft_strncmp(tmp, tk->s,
				ft_strlen(tmp)) == 0))
			break ;
		if (contain_var(tmp))
			tmp = hrdc_convert(mini, tmp);
		ft_putendl_fd(tmp, mini->tab[i][1]);
	}
	if (tmp)
		free(tmp);
	g_sig = 0;
	exit(0);
}

// void	hrdc_syntax(t_shell *mini)
// {
// 	t_hrdc	*cp;
// 	int		i;

// 	cp = mini->hrdc;
// 	i = -1;
// 	while (cp)
// 	{
// 		while (cp->content[++i])
// 		{
// 			if (contain_var(cp->content[i]))
// 				cp->content[i] = hrdc_convert(mini, cp->content[i]);
// 		}
// 		cp = cp->next;
// 	}
// }
