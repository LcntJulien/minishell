/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hrdc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:57:43 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/01 11:59:30 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*hrdc_convert(t_shell *mini, char *s)
{
	char	*cur;
	char	*tmp;
	char	*iter;
	int		i;

	cur = NULL;
	tmp = NULL;
	iter = NULL;
	i = -1;
	while (s && s[++i])
	{
		if (s[i] == '$' && !(is_quote(s) && quote_state(s, i) == 1))
		{
			cur = get_vname(s, i);
			iter = get_nvar(mini, cur);
			tmp = rewrite(mini, s, cur, i);
			free(s);
			s = tmp;
			i += (ft_strlen(iter) - 1);
			free2(cur, iter);
		}
	}
	return (s);
}

void	redir_hrdc(t_shell *mini, t_token *cur)
{
	char	*tmp;

	tmp = NULL;
	mini->in = open(HRDC, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (mini->in < 0)
		fds_err(mini, HRDC);
	while (1)
	{
		tmp = readline("\033[0;35m\033[1m▸ \033[0m");
		if (!tmp || (tmp && tmp[0] && ft_strncmp(tmp, cur->s,
					ft_strlen(tmp)) == 0))
			break ;
		if (contain_var(tmp))
			tmp = hrdc_convert(mini, tmp);
		ft_putendl_fd(tmp, mini->in);
	}
	close(mini->in);
	mini->in = open(HRDC, O_RDONLY);
	dup2(mini->in, STDIN_FILENO);
	if (tmp)
		free(tmp);
}

int	hrdc_filler(t_shell *mini, char *cur, int h)
{
	char	*tmp;

	tmp = NULL;
	define_signals_hrdc();
	while (1)
	{
		tmp = readline("\033[0;35m\033[1m▸ \033[0m");
		if (!tmp || (tmp && tmp[0] && ft_strncmp(tmp, cur,
					ft_strlen(tmp)) == 0))
			break ;
		if (contain_var(tmp))
			tmp = hrdc_convert(mini, tmp);
		ft_putendl_fd(tmp, mini->htab[h][1]);
	}
	if (tmp)
		free(tmp);
	return (0);
}

int	hrdc_handler(t_shell *mini, t_token *cur, int h)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		err_manager(mini, NULL, 2);
	if (pid == 0)
	{
		g_sig = 2;
		if (hrdc_filler(mini, cur->s, h) == -1)
			exit(-1);
		close(mini->htab[h][1]);
		exit(0);
	}
	close(mini->htab[h][1]);
	waitpid(pid, &status, 0);
	if (status != 0)
		return (1);
	g_sig = 0;
	return (0);
}

int	hrdc_manager(t_shell *mini)
{
	t_token	*cp;
	int		i;
	int		h;

	cp = mini->token;
	i = -1;
	h = 0;
	if (nb_hrdc(mini))
	{
		alloc_htab(mini, nb_hrdc(mini));
		while (++i < mini->ncmd)
		{
			if (is_redir(cp, 1) && is_hrdc(cp))
			{
				if (hrdc_handler(mini, cur_hrdc(cp), h))
				{
					mini_free(mini);
					return (1);
				}
				h++;
			}
			cp = next_cmd(cp);
		}
	}
	return (0);
}
