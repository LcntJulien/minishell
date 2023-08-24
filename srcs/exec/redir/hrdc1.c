/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hrdc1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:08:10 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/24 17:51:25 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	redir_hrdc(t_shell *mini, t_token *cur)
{
	t_hrdc	*cp;
	int		j;

	cp = mini->hrdc;
	j = -1;
	mini->in = open(HRDC, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (mini->in < 0)
		fds_err(mini, HRDC);
	while (cp->next && cp->idx != cur->idx)
		cp = cp->next;
	while (cp->content[++j])
		ft_putendl_fd(cp->content[j], mini->in);
	close(mini->in);
	mini->in = open(HRDC, O_RDONLY);
	dup2(mini->in, STDIN_FILENO);
}

void	ctrl_d_hrdc(t_shell *mini, int idx)
{
	t_hrdc	*cp;
	t_hrdc	*tmp;
	int		i;

	cp = mini->hrdc;
	tmp = NULL;
	i = -1;
	while (cp->idx != idx)
		cp = cp->next;
	while (cp->content[++i])
		ft_putstr_fd(cp->content[i], 1);
	free_tab(cp->content);
	tmp = cp->next;
	free(cp);
	cp = tmp;
}

int	hrdc_filler(t_shell *mini, t_hrdc *hrdc, char **tab, int size)
{
	int i;

	i = -1;
	hrdc->content = ft_calloc(sizeof(char *), (size + 1));
	if (!hrdc->content)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd("can't allocate space", 2);
		return (1);
	}
	while (tab[++i] != NULL)
		hrdc->content[i] = ft_strdup(tab[i]);
	add_hrdc(mini, hrdc);
	return (0);
}