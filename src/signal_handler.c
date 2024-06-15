/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:09:16 by pclaus            #+#    #+#             */
/*   Updated: 2024/06/15 16:38:08 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	custom_sigint_handler_function(int signal)
{
	int	wstat;
	int	sig;
	pid_t	pid;

	(void)signal;
	write(1, "\n", 1);
	if (!g_shell_stats.process_is_running)
	{
		g_shell_stats.prev_exit = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		kill(g_shell_stats.cmd_pid, SIGINT);
		(void)pid;
		pid = waitpid(g_shell_stats.cmd_pid, &wstat, 0);
		ft_putstr_fd("SIGINT: waitpid=", 1);
		ft_putnbr_fd(pid, 1);
		write(1, "\n", 1);
		if (WIFEXITED(wstat))
		{
			ft_putstr_fd("exited: ", 1);
			ft_putnbr_fd(WEXITSTATUS(wstat), 1);
			write(1, "\n", 1);
			g_shell_stats.prev_exit = WEXITSTATUS(wstat);
		}
		else if (WIFSIGNALED(wstat))
		{
			sig = WTERMSIG(wstat);
			ft_putstr_fd("sig: ", 1);
			ft_putnbr_fd(sig, 1);
			write(1, "\n", 1);
			if (sig == 3)
			{
				printf("Quit (core dumped)\n");
				g_shell_stats.prev_exit = 131;
			}
			else
				g_shell_stats.prev_exit = 130;
			g_shell_stats.process_is_running = 0;
		}
	}
}

void	handle_sigint(void)
{
	struct sigaction	sa;
	sigset_t			signal_set;

	memset(&sa, 0, sizeof(sa));
	sigemptyset(&signal_set);
	sa.sa_mask = signal_set;
	sa.sa_handler = &custom_sigint_handler_function;
	sigaction(SIGINT, &sa, NULL);
}

void	handle_sigquit(void)
{
	struct sigaction	sa;
	sigset_t			signal_set;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&signal_set);
	sa.sa_mask = signal_set;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_sigquit_child(void)
{
	struct sigaction	sa;
	sigset_t			signal_set;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&signal_set);
	sa.sa_mask = signal_set;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sa, NULL);
}
