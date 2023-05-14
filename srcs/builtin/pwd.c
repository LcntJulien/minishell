/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:09:37 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/14 18:18:20 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd(void)
{
	char *cwd;
	
	cwd = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	    printf("%s\n", cwd);
	else
		perror(""); // a définir
}