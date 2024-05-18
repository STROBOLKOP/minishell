/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:28:33 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/18 21:52:44 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_lexer_state(t_lexeme *lexeme, char *line, int *index)
{
	if (line[*index] == 39)
		lexeme->lexing_state = SQ;
	else if ((line[*index] >= 'a' && line[*index] <= 'z')
			|| (line[*index] >= 'A' && line[*index] <= 'Z'))
		lexeme->lexing_state = UNQUOTED;
	else if (line[*index] == 124 || line[*index] == 38 || line[*index] == 59
			|| line[*index] == 40 || line[*index] == 41 || line[*index == 60
			|| line[*index] == 61])
		lexeme->lexing_state = META;
}

void	handle_single_quotes(t_lexeme *lexeme, char *line, int *index)
{
	(*index)++;
	lexeme->lexing_state = SQ;
	while (lexeme->lexing_state == SQ)
	{
		ft_strjoin_char(&lexeme->string, (line[*index]));
		(*index)++;
		if (line[*index] == 39)
		{
			lexeme->lexing_state = UNQUOTED;
			add_token_to_end(&lexeme->head, create_token(lexeme->string));
			lexeme->string = NULL;
			break ;
		}
	}
	(*index)++;
}

void	handle_unquoted(t_lexeme *lexeme, char *line, int *index)
{
	while (lexeme->lexing_state == UNQUOTED)
	{
		ft_strjoin_char(&lexeme->string, (line[*index]));
		(*index)++;
		if (!(line[*index] >= 'a' && line[*index] <= 'z')
			|| line[*index] == '\0')
		{
			lexeme->lexing_state = START;
			add_token_to_end(&lexeme->head, create_token(lexeme->string));
			lexeme->string = NULL;
			break ;
		}
	}
}
