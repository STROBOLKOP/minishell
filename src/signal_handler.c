/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:09:16 by pclaus            #+#    #+#             */
/*   Updated: 2024/06/13 17:38:44 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	custom_sigint_handler_function(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	if (!g_shell_stats.process_is_running)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	custom_sigint_handler_function_child(int signal)
{
	(void)signal;
	write(1, "haha\n", 5);
	
}
//write one signal handler function to handle both cases

void	handle_sigint(void)
{
	struct sigaction	sa;
	sigset_t	signal_set;

	ft_memset(&sa, 0, sizeof(sa));
	sigfillset(&signal_set);
	sa.sa_mask = signal_set;
	sa.sa_handler = &custom_sigint_handler_function;
	sigaction(SIGINT, &sa, NULL);
}

void	handle_sigint_child(void)
{
	struct sigaction	sa;
	sigset_t	signal_set;

	ft_memset(&sa, 0, sizeof(sa));
	sigfillset(&signal_set);
	sa.sa_mask = signal_set;
	sa.sa_handler = &custom_sigint_handler_function_child;
	sigaction(SIGINT, &sa, NULL);
}




void	handle_sigquit(void)
{
	struct sigaction	sa;
	sigset_t	signal_set;

	ft_memset(&sa, 0, sizeof(sa));
	sigfillset(&signal_set);//not allowed 
	sa.sa_mask = signal_set;
	sa.sa_handler = SIG_IGN;

	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_sigquit_child(void)
{
	struct sigaction	sa;
	sigset_t	signal_set;

	ft_memset(&sa, 0, sizeof(sa));
	sigfillset(&signal_set);//not allowed 
	sa.sa_mask = signal_set;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sa, NULL);
}
