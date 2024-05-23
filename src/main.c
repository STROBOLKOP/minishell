/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:32:43 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/23 15:53:04 by efret            ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	if (ac > 1)
		exit_handler(0);
	(void)av;
	(void)envp;
	interactive();
	exit_handler(0);
	return (0);
}
