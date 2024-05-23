/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 12:01:35 by elias             #+#    #+#             */
/*   Updated: 2024/05/23 15:48:30 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_handler(int status)
{
	rl_clear_history();
	if (!status)
		write(2, "exit\n", 5);
	exit(status);
}
