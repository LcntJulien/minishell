/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:16:06 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/17 17:16:07 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cd(char *path)
{
	if (chdir(path) == -1)
		perror("Invalid path");
	else
	{

	}
	// gerer la mise a jour de env lorsque le path change: OLDPWD a integre en fin d'environnement
	
}