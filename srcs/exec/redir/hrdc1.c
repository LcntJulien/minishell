/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hrdc1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:08:10 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/29 18:33:03 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
		if (s[i] == '$' && !(is_quote(s) && quote_state(s, i) == 1))
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

void	redir_hrdc(t_shell *mini, t_token *cur)
{
	char	*tmp;

	tmp = NULL;
	mini->in = open(HRDC, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (mini->in < 0)
		fds_err(mini, HRDC);
	while (1)
	{
		tmp = readline("\033[0;35m\033[1m▸ \033[0m");
		if (!tmp || (tmp && tmp[0] && ft_strncmp(tmp, cur->s,
					ft_strlen(tmp)) == 0))
			break ;
		if (contain_var(tmp))
			tmp = hrdc_convert(mini, tmp);
		ft_putendl_fd(tmp, mini->in);
	}
	close(mini->in);
	mini->in = open(HRDC, O_RDONLY);
	dup2(mini->in, STDIN_FILENO);
	if (tmp)
		free(tmp);
}

int	is_hrdc(t_token *tk)
{
	t_token	*cp;
	t_token	*cur;

	cp = tk;
	cur = NULL;
	while (cp->prev && cp->prev->type != PIPE)
		cp = cp->prev;
	while (cp->next && cp->type != PIPE)
	{
		if (cp->next && (cp->type == INPUT || cp->type == HEREDOC))
			cur = cp->next;
		cp = cp->next;
	}
	if (cur->prev->type == HEREDOC)
		return (1);
	return (0);
}

t_token	*cur_hrdc(t_token *tk)
{
	t_token	*cp;
	t_token	*cur;

	cp = tk;
	cur = NULL;
	while (cp->prev && cp->prev->type != PIPE)
		cp = cp->prev;
	while (cp->next && cp->type != PIPE)
	{
		if (cp->next && (cp->type == INPUT || cp->type == HEREDOC))
			cur = cp->next;
		cp = cp->next;
	}
	if (cur->prev->type == HEREDOC)
		return (cur);
	return (NULL);
}

int	nb_hrdc(t_shell *mini)
{
	t_token	*cp;
	int i;
	int r;
	
	cp = mini->token;
	i = -1;
	r = 0;
	while (++i < mini->ncmd)
	{
		if (is_redir(cp, 1) && is_hrdc(cp))
			r++;
		cp = next_cmd(cp);
	}
	return (r);
}

void	hrdc_manager(t_shell *mini)
{
	t_token	*cp;
	pid_t	*pid;
	int		i;

	cp = mini->token;
	pid = malloc(sizeof(pid_t) * nb_hrdc(mini));
	i = -1;
	while (++i < mini->ncmd)
	{
		if (is_redir(cp, 1) && is_hrdc(cp))
		{
			pid[i] = fork();
			if (pid[i] < 0)
				err_manager(mini, NULL, 2);
			else if (!pid[i])
				heredoc_handler(mini, cur_hrdc(cp), i);
		}
		cp = next_cmd(cp);
	}
	i = -1;
	while (++i < mini->ncmd)
	{
		waitpid(pid[i], &mini->hrtn, 0);
		if (mini->hrtn == 256)
			mini_free(mini);
	}
	
}
