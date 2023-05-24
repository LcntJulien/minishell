/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:15:31 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/24 14:51:01 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd(t_shell *mini)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path != NULL)
		printf("%s\n", path);
	return ;
}
