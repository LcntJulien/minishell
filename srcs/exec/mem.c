/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:49:24 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/12 14:12:13 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mini_free(t_shell *mini)
{
	if (g_sig != 0)
		define_last(mini);
	free_pipe(mini);
	free_paths(mini);
	free_args(mini);
	free_token(mini);
	free_htab(mini);
	if (mini->pid)
		free(mini->pid);
	mini->pid = NULL;
	if (mini->cmd)
		free(mini->cmd);
	mini->cmd = NULL;
	if (mini->line)
		free(mini->line);
	mini->line = NULL;
	mini->ncmd = 0;
}

void	pipe_alloc(t_shell *mini)
{
	int	i;

	i = -1;
	mini->tab = ft_calloc(sizeof(int *), mini->ncmd + 1);
	if (!mini->tab)
		err_manager(mini, NULL, 3);
	while (++i < mini->ncmd)
	{
		mini->tab[i] = ft_calloc(sizeof(int), 2);
		if (!mini->tab[i])
			err_manager(mini, NULL, 3);
	}
	mini->pid = malloc(sizeof(pid_t) * mini->ncmd);
	if (!mini->pid)
		err_manager(mini, NULL, 3);
	i = -1;
	while (++i < mini->ncmd)
		if (pipe(mini->tab[i]) < 0)
			err_manager(mini, NULL, 1);
}

void	close_output(t_token *tk, t_token *cur)
{
	t_token	*cp;
	int		fd;

	cp = tk;
	fd = 0;
	while (cp->prev && cp->prev->type != PIPE)
		cp = cp->prev;
	while (cp && cp->type != PIPE)
	{
		if (cp->next && cp->type == OUTPUT && cp->next->idx != cur->idx)
		{
			fd = open(cp->next->s, O_CREAT | O_RDWR | O_TRUNC, 0644);
			close(fd);
		}
		cp = cp->next;
	}
}

void	hrdc_close(t_shell *mini, int i, int sw)
{
	int	j;

	j = -1;
	fprintf(stderr, "hrdc_close\n");
	if (sw)
	{
		while (++j < nb_hrdc(mini))
		{
			if (j != i)
			{
				fprintf(stderr, "close(mini->htab[%d][0]);\n", j);
				close(mini->htab[j][0]);
			}
			fprintf(stderr, "close(mini->htab[%d][1]);\n", j);
			close(mini->htab[j][1]);
		}
	}
	else
	{
		while (++j < nb_hrdc(mini))
		{
			fprintf(stderr, "close(mini->htab[%d][0]);\n", j);
			fprintf(stderr, "close(mini->htab[%d][1]);\n", j);
			close(mini->htab[j][0]);
			close(mini->htab[j][1]);
		}
	}
}

void	close_pipes(t_shell *mini, int i, int sw)
{
	int	j;

	j = -1;
	fprintf(stderr, "close pipe\n");
	if (sw)
	{
		while (++j < mini->ncmd)
		{
			if (j != i)
			{
				fprintf(stderr, "close(mini->tab[%d][0]);\n", j);
				close(mini->tab[j][0]);
			}
			if (j != (i + 1))
			{
				fprintf(stderr, "close(mini->tab[%d][1]);\n", j);
				close(mini->tab[j][1]);
			}
		}
		if (i == 0)
		{
			fprintf(stderr, "close(mini->tab[%d][0]);\n", i);
			close(mini->tab[i][0]);
		}
	}
	else
	{
		while (++j < mini->ncmd)
		{
			fprintf(stderr, "close(mini->tab[%d][0]);\n", j);
			fprintf(stderr, "close(mini->tab[%d][1]);\n", j);
			close(mini->tab[j][0]);
			close(mini->tab[j][1]);
		}
	}
}
