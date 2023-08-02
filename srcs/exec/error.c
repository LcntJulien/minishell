/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:39:05 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/01 17:08:19 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_files(t_shell *mini, t_token *tk, char *s)
{
	t_token	*cp;
	int		fd;

	cp = tk;
	fd = 0;
	while (cp->next && cp->next->type != PIPE)
	{
		if ((cp->type == OUTPUT || cp->type == APPEND)
			&& (ft_strncmp(cp->next->s, s, ft_strlen(cp->next->s))))
		{
			fd = open(cp->next->s, O_WRONLY | O_TRUNC);
			if (fd < 0)
				fds_err(mini, cp->next->s);
			close(fd);
		}
		cp = cp->next;
	}
}

void	fds_err(t_shell	*mini, char	*fname)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(fname, 2);
	ft_putendl_fd("; no such file or directory", 2);
	mini->rtn = 1;
	exit(1);
}

void	err_manager(t_shell *mini, t_token *tk, int err)
{
	ft_putstr_fd("minishell: ", 2);
	if (!err)
	{
		if (tk)
			ft_putstr_fd(tk->s, 2);
		ft_putendl_fd(": command not found", 2);
		mini->rtn = 127;
		exit(127);
	}
	else if (err == 1)
		ft_putendl_fd("error creating pipe", 2);
	else if (err == 2)
		ft_putendl_fd("error forking process id", 2);
	mini->rtn = EXIT_FAILURE;
	exit(EXIT_FAILURE);
}
