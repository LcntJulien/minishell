/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:15:31 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/10 16:47:02 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_pwd(t_shell *mini)
{
	char	*pathnewline;
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		ft_exit(mini, 1);
	pathnewline = ft_strjoin(path, "\n");
	ft_putstr_fd(pathnewline, STDOUT_FILENO);
	free_str(path);
	free_str(pathnewline);
	return ;
}
