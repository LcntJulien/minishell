/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:15:31 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/10 01:28:27 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_pwd(t_shell *mini)
{
	char	*path;
	
	path = getcwd(NULL, 0);
	if (!path)
		ft_exit(mini, 1);
	printf("%s\n", path);
	return ;
}
