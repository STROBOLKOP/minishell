/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:32:43 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/10 19:48:16 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*prompt;
	char	*line;

	prompt = "minihell> ";
	while (1)
	{
		line = readline(prompt);
		printf("You have entered: %s\n", line);
		if (exact_match(line, "exit") || exact_match(line, "echo")
			|| exact_match(line, "cd") || exact_match(line, "pwd")
			|| exact_match(line, "export") || exact_match(line, "unset")
			|| exact_match(line, "env"))
			check_for_builtins(line);
	}
	return (0);
}
