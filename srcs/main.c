/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecorne <jlecorne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:07:16 by jlecorne          #+#    #+#             */
/*   Updated: 2023/08/29 01:05:47 by jlecorne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	hrdc_manager(t_shell *mini)
{
	t_token	*tk;
	pid_t	pid;

	tk = mini->token;
	while (tk && tk->next != NULL)
	{
		if (tk->type == HEREDOC)
		{
			pid = fork();
			if (pid < 0)
				err_manager(mini, NULL, 2);
			else if (!pid)
			{
				g_sig = 2;
				heredoc_handler(mini, tk->next);
			}
			waitpid(pid, &mini->hrtn, 0);
			g_sig = 0;
			if (mini->hrtn == 256)
				mini_free(mini);
		}
		tk = tk->next;
	}
	hrdc_syntax(mini);
}

static void	startshell(t_shell *mini, char **env, int *histo,
		struct termios *term)
{
	mini->rtn = 0;
	mini->exit = 0;
	mini->pid = 0;
	mini->ncmd = 0;
	mini->in = 0;
	mini->out = 0;
	mini->hrtn = 0;
	mini->cmd = NULL;
	mini->tab = NULL;
	mini->args = NULL;
	mini->paths = NULL;
	mini->line = NULL;
	mini->tab = NULL;
	mini->token = NULL;
	mini->hrdc = NULL;
	alloc_env(mini, env);
	mini->home = ft_strdup(getenv("HOME"));
	if (!create_history(histo))
		ft_exit_plus(mini, "Fail to create/iniate history\n", 1);
	if (tcgetattr(STDIN_FILENO, term) == -1)
		ft_exit_plus(mini, "Fail to get terminal attributes\n", 1);
	rl_catch_signals = 0;
}

static void	args(int ac, char **av)
{
	(void)av;
	g_sig = 0;
	define_signals();
	if (ac > 1)
	{
		ft_putstr_fd("Launch without any arguments\n", STDERR_FILENO);
		exit(1);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell			mini;
	struct termios	term;
	int				histo;

	args(ac, av);
	startshell(&mini, env, &histo, &term);
	while (1)
	{
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
			ft_exit_plus(&mini, "Fail to reload minishell attributes\n", 1);
		mini.line = readline("\033[0;35m\033[1mminishell ▸ \033[0m");
		if (!mini.line)
			break ;
		if (mini.line[0])
		{
			add_histo(mini.line, histo);
			parse_input(&mini);
			hrdc_manager(&mini);
			minishell(&mini);
		}
		mini_free(&mini);
	}
	ft_exit_all(&mini, histo, 130);
}
