/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_process.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:53:11 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/07 18:47:28 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_process(t_shell *mini)
{
	t_token	*list;

	list = mini->token;
	if (mini->token && !ft_strncmp(mini->token->s, "echo", 4))
		b_echo(mini, list);
	else if (mini->token && !ft_strncmp(mini->token->s, "cd", 2))
		b_cd(mini, list);
	//else if (mini->token && !ft_strncmp(mini->token->s, "pwd", 3))
		//b_pwd(mini, list);
	else if (mini->token && !ft_strncmp(mini->token->s, "export", 6))
		b_export(mini, list);
	//else if (mini->token && !ft_strncmp(mini->token->s, "unset", 5))
		//b_unset(mini, list);
	else if (mini->token && !ft_strncmp(mini->token->s, "env", 3))
		b_env(mini);
	//else if (mini->token && !ft_strncmp(mini->token->s, "exit", 4))
		//b_exit(mini, list);
	return ;
}