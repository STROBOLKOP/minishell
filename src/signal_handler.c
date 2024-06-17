/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:09:16 by pclaus            #+#    #+#             */
/*   Updated: 2024/06/17 20:53:36 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	custom_sigint_handler_function(int signal)
{

	(void)signal;
	if (!g_shell_stats.process_is_running)
	{
		g_shell_stats.prev_exit = EOWNERDEAD;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_set_prompt("\033[31m->\033[0m minishell> ");// Only needed for the red arrow
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sigchld_handler(int signal, siginfo_t *info, void *ucontext)
{
	(void)signal;
	(void)ucontext;
	switch (info->si_code) {
		case CLD_EXITED:
			if (info->si_pid == g_shell_stats.cmd_pid)
				g_shell_stats.prev_exit = info->si_status;
			break ;
		case CLD_KILLED:
			g_shell_stats.prev_exit = EOWNERDEAD;
			if (info->si_pid == g_shell_stats.cmd_pid)
			{
				g_shell_stats.process_is_running = 0;
				ft_putstr_fd("\n", 1);
			}
			break ;
		case CLD_DUMPED:
			g_shell_stats.prev_exit = ENOTRECOVERABLE;
			if (info->si_pid == g_shell_stats.cmd_pid)
			{
				g_shell_stats.process_is_running = 0;
				ft_putstr_fd("Quit (core dumped)\n", 1);
			}
			break ;
		default:
			break ;
	}
}

void	handle_sigchld(void)
{
	struct sigaction	sa;
	sigset_t			signal_set;

	memset(&sa, 0, sizeof(sa));
	sigemptyset(&signal_set);
	sa.sa_mask = signal_set;
	sigaddset(&signal_set, SIGINT);
	sa.sa_sigaction = &sigchld_handler;
	sa.sa_flags |= SA_SIGINFO;
	sigaction(SIGCHLD, &sa, NULL);
}

void	handle_sigint(void)
{
	struct sigaction	sa;
	sigset_t			signal_set;

	memset(&sa, 0, sizeof(sa));
	sigemptyset(&signal_set);
	sa.sa_mask = signal_set;
	sigaddset(&signal_set, SIGCHLD);
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
