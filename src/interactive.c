/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:45:03 by efret             #+#    #+#             */
/*   Updated: 2024/05/31 11:36:55 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	disp_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token type %i: %s\n", tokens->tag, tokens->str);
		tokens = tokens->next;
	}
}

void	interactive(void)
{
	char	*prompt;
	char	*line;
	t_token	*tokens;

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
			tokens = lexer(line);
			printf("\nIn Interactive\n");
			disp_tokens(tokens);
		}
		free(line);
	}
	exit_handler(0);
}
