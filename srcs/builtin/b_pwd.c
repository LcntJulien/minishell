/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:26:06 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/17 16:38:46 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd(t_shell *mini)
{
	char *path;

	path = getcwd(NULL, 0);
	if (path =! NULL)
		printf("%s\n", path);
	else
		perror("");
}
