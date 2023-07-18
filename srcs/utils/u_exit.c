/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:11:51 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/18 10:34:30 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(t_shell *mini, char *err, int rtn)
{
	mini->rtn = rtn;
	free_env(mini);
	perror(err);
	exit(mini->rtn);
}

void	ft_exit_plus(t_shell *mini, char *err, int rtn)
{
	mini->rtn = rtn;
	if (mini->home)
		free_str(mini->home);
	if (mini->env)
		free_env(mini);
	if (mini->token)
		listfree(mini->token);
	if (mini->args)
		free_tab(mini->args);
	if (mini->paths)
		free_tab(mini->paths);
	perror(err);
	exit(mini->rtn);
}

void	ft_exit_all(t_shell *mini, int histo, int rtn)
{
	close(histo);
	mini_free(mini);
	if (mini->env)
		free_env(mini);
	exit(rtn);
}
