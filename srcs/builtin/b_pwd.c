/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:09:37 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/16 10:46:09 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd(t_shell *mini)
{
	char *cwd;
	
	cwd = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	    printf("%s\n", cwd);
	else
		perror(""); // a définir
}