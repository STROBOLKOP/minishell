/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:49:13 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/30 18:32:16 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
		write(1, "\nSIGINT intercepted\n", 20);
}

void	handle_sigint(void)
{
	struct sigaction	sa;


	sa.sa_handler = &sigint_handler;
	sigaction(SIGINT, &sa, NULL);
}

void	handle_sigquit(void)
{
	struct sigaction sa;

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
