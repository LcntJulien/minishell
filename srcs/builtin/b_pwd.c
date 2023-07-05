/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:15:31 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/04 15:02:10 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_pwd(t_shell *mini)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		ft_exit(mini, 1);
	path = ft_strjoin(path, "\n");
	ft_putstr_fd(path, STDOUT_FILENO);
	free(path);
	return ;
}
