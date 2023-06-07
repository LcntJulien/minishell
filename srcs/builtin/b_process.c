/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_process.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:53:11 by jmathieu          #+#    #+#             */
/*   Updated: 2023/06/07 16:07:52 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_process(t_shell *mini)
{
	/* il faut bien avoir le nombre de redirection */
	/* Voir pour la sortie si on peut pas l'ajouter */
	//if (mini->token->redir == 0)
	//{
		if (mini->token && !ft_strncmp(mini->token->s, "echo", 4))
			b_echo(mini);
		else if (mini->token && !ft_strncmp(mini->token->s, "cd", 2))
			b_cd(mini);
		//else if (mini->token && !ft_strncmp(mini->token->s, "pwd", 3))
			//b_pwd(mini);
		else if (mini->token && !ft_strncmp(mini->token->s, "export", 6))
			b_export(mini);
		//else if (mini->token && !ft_strncmp(mini->token->s, "unset", 5))
			//b_unset(mini);
		else if (mini->token && !ft_strncmp(mini->token->s, "env", 3))
			b_env(mini);
		//else if (mini->token && !ft_strncmp(mini->token->s, "exit", 4))
			//b_exit(mini);
		return ;
	//}
}
