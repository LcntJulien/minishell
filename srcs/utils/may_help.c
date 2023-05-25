/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils+.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmathieu <jmathieu@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:27:30 by jmathieu          #+#    #+#             */
/*   Updated: 2023/05/24 15:30:03 by jmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	find_pwd(t_shell *mini)
{
	int	i;

	i = -1;
	while (mini->env[++i])
	{
		if (!ft_strncmp(mini->env[i], "PWD=", 4))
			mini->pwd = ft_substr(mini->env[i], 4,
					ft_strlen(mini->env[i]) - 4);
		if (!ft_strncmp(mini->env[i], "OLDPWD=", 7))
			mini->oldpwd = ft_substr(mini->env[i], 7,
					ft_strlen(mini->env[i]) - 7);
	}
}
