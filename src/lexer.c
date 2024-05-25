/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:56:40 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/25 10:17:43 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer(char *line)
{
	t_lexeme	lexeme;
	static int	index;

	index = 0;
	lexeme.lexing_state = START;
	lexeme.string = NULL;
	lexeme.head = NULL;
	while (line && line[index])
	{
		update_lexer_state(&lexeme, line, &index);
		if (lexeme.lexing_state == UNQUOTED)
			handle_unquoted(&lexeme, line, &index);
		if (lexeme.lexing_state == SQ)
			handle_single_quotes(&lexeme, line, &index);
		if (lexeme.lexing_state == DQ)
			handle_double_quotes(&lexeme, line, &index);
		if (lexeme.lexing_state == META)
			handle_meta_char(&lexeme, line, &index);
		if (lexeme.lexing_state == SP)
			handle_space(&lexeme, line, &index);
		if (lexeme.lexing_state == DOLLAR)
			handle_dollar(&lexeme, line, &index);
	}
//	print_list(&lexeme.head);
	free_list(&lexeme.head);
}
