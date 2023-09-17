/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hrdc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:57:43 by jlecorne          #+#    #+#             */
/*   Updated: 2023/09/17 15:35:59 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	alloc_htab(t_shell *mini, int nb)
{
	int	i;

	i = -1;
	mini->htab = malloc(sizeof(int *) * nb);
	if (!mini->htab)
		err_manager(mini, NULL, 3);
	while (++i < nb)
	{
		mini->htab[i] = malloc(sizeof(int) * 2);
		if (!mini->htab[i])
			err_manager(mini, NULL, 3);
	}
	i = -1;
	while (++i < nb)
		if (pipe(mini->htab[i]) < 0)
			err_manager(mini, NULL, 1);
}

char	*hrdc_convert(t_shell *mini, char *s)
{
	char	*cur;
	char	*tmp;
	char	*iter;
	int		i;

	cur = NULL;
	tmp = NULL;
	iter = NULL;
	i = -1;
	while (s && s[++i])
	{
		if (s[i] == '$')
		{
			cur = get_vname(s, i);
			iter = get_nvar(mini, cur);
			tmp = rewrite(mini, s, cur, i);
			free(s);
			s = tmp;
			i += (ft_strlen(iter) - 1);
			free2(cur, iter);
		}
	}
	return (s);
}

void	hrdc_filler(t_shell *mini, t_token *cur)
{
	char			*tmp;

	tmp = NULL;
	signals_hrdc();
	while (1 && g_sig != 42)
	{
		tmp = readline("\033[0;35m\033[1m▸ \033[0m");
		if (!tmp || (tmp && tmp[0] && ft_strncmp(tmp, cur->s,
					ft_strlen(tmp)) == 0))
			break ;
		if (contain_var(tmp))
			tmp = hrdc_convert(mini, tmp);
		ft_putendl_fd(tmp, mini->htab[0][1]);
	}
	if (tmp)
		free(tmp);
	exit(0);
}

void	hrdc(t_shell *mini, t_token *cur)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		err_manager(mini, NULL, 2);
	else if (!pid)
	{
		hrdc_filler(mini, cur);
		exit(0);
	}
	waitpid(pid, &mini->rtn, 0);
	mini->rtn = WEXITSTATUS(mini->rtn);
	g_sig = 1;
	if (mini->rtn)
		mini_free(mini);
}

//int	hrdc_filler(t_shell *mini, char *cur, int h)
//{
	//char	*tmp;

	//tmp = NULL;
	//signals_hrdc();
	//while (1)
	//{
		//tmp = readline("\033[0;35m\033[1m▸ \033[0m");
		//if (!tmp || (tmp && tmp[0] && ft_strncmp(tmp, cur,
					//ft_strlen(tmp)) == 0))
			//break ;
		//if (contain_var(tmp))
			//tmp = hrdc_convert(mini, tmp);
		//ft_putendl_fd(tmp, mini->htab[h][1]);
	//}
	//if (tmp)
		//free(tmp);
	//return (0);
//}

//int	hrdc_handler(t_shell *mini, t_token *cur, int h)
//{
	//pid_t	pid;
	//int		status;

	//status = 0;
	//pid = fork();
	//if (pid == -1)
		//err_manager(mini, NULL, 2);
	//if (pid == 0)
	//{
		//g_sig = 2;
		//if (hrdc_filler(mini, cur->s, h) == -1)
			//exit(1);
		//exit(0);
	//}
	//waitpid(pid, &status, 0);
	//status = WEXITSTATUS(status);
	//g_sig = 0;
	//if (status == 256)
		//mini->rtn = 1;
	//if (status != 0)
		//return (1);
	//return (0);
//}

//int	hrdc_manager(t_shell *mini)
//{
	//t_token	*cp;
	//int		i;
	//int		h;

	//cp = mini->token;
	//i = -1;
	//h = 0;
	//if (nb_hrdc(mini))
	//{
		//alloc_htab(mini, nb_hrdc(mini));
		//while (++i < mini->ncmd)
		//{
			//if (is_redir(cp, 1) && is_hrdc(cp))
			//{
				//if (hrdc_handler(mini, cur_hrdc(cp), h))
				//{
					//mini_free(mini);
					//return (1);
				//}
				//h++;
			//}
			//cp = next_cmd(cp);
		//}
	//}
	//return (0);
//}
