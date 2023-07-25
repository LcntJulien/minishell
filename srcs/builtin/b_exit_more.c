/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit_more.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 09:56:15 by jmathieu          #+#    #+#             */
/*   Updated: 2023/07/25 15:30:23 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_until(t_shell *mini)
{
	if (mini->home)
		free_str(mini->home);
	if (mini->env)
		free_env(mini);
	if (mini->token)
		free_token(mini, mini->token);
	if (mini->args)
		free_tab(mini->args);
	if (mini->paths)
		free_tab(mini->paths);
}

void	exit_too_much(t_shell *mini)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin("minishell: exit: ", mini->token->next->s);
	s2 = ft_strjoin(s1, ": numeric argument required\n");
	free_str(s1);
	ft_putstr_fd(s2, STDERR_FILENO);
	free_str(s2);
	exit_until(mini);
	exit(255);
}
