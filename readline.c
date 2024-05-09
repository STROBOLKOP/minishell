/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:48:46 by efret             #+#    #+#             */
/*   Updated: 2024/05/09 11:28:11 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Compile with flag -lreadline */
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

char	*get_input(char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (line && *line)
		add_history(line);
	return (line);
}

int	main(void)
{
	char	*line;

	line = get_input("shell$>");
	while (line)
	{
		if (line && *line)
		{
			printf("%s\n", line);
		}
		free(line);
		line = get_input("shell$>");
	}
	printf("exit\n");
	rl_clear_history();
	return (0);
}
