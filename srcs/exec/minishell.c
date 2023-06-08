/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:28:35 by jlecorne          #+#    #+#             */
/*   Updated: 2023/06/08 19:04:42 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 - connaitre nb cmd -> parcourir liste chercher pipe
 - ouvrir scopes pour execution -> dup stdout/stdin/autre & fork pid pour attente d'exec
 - determiner process -> builtin/execve
 - boucler sur nb cmd -> set mini->token sur prochaine cmd/decla...
*/

int nb_cmd(t_shell  *mini)
{
    t_token *tk;
    int r;

    tk = mini->token;
    r = 0;
    while (tk)
    {
        if (tk->type == PIPE)
            r++;
        tk = tk->next;
    }
    return (r + 1);
}

void	minishell(t_shell *mini)
{

}