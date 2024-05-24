/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:45:03 by efret             #+#    #+#             */
/*   Updated: 2024/05/24 14:45:18 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	interactive(void)
{
	char	*prompt;
	char	*line;

	prompt = "minihell> ";
	while (1)
	{
		line = readline(prompt);
		if (!line)
			exit_handler(errno);
		if (line && *line)
		{
			add_history(line);
			printf("You have entered: %s\n", line);
		}
		check_for_builtins(line);
		free(line);
	}
	exit_handler(0);
}
