/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:32:43 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/30 18:32:55 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*prompt;
	char	*line;


	handle_sigint();
	handle_sigquit();
	prompt = "minihell> ";
	while (1)
	{
		line = readline(prompt);
		if (!line)
			exit_handler(errno);
		if (line && *line)
		{
			printf("%s\n", line);
			add_history(line);
			lexer(line);
		}
		// check_for_builtins(line);
	}
	return (0);
}
