/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:20:46 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/20 10:47:49 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_single_quotes(t_lexeme *lexeme, char *line, int *index)
{
	(*index)++;
	while (lexeme->lexing_state == SQ)
	{
		ft_strjoin_char(&lexeme->string, (line[*index]));
		(*index)++;
		if (line[*index] == 39)
		{
			reset_lexer_state(lexeme);
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
		if (!is_regular_character(line[*index]) || (line[*index] == '\0'))
		{
			reset_lexer_state(lexeme);
			break ;
		}
	}
}

void	handle_space(t_lexeme *lexeme, char *line, int *index)
{
	while (lexeme->lexing_state == SP)
	{
		(*index)++;
		if (line[*index] != 32)
		{
			lexeme->lexing_state = START;
			break ;
		}
	}
}

void	handle_double_quotes(t_lexeme *lexeme, char *line, int *index)
{
	(*index)++;
	while (lexeme->lexing_state == DQ)
	{
		ft_strjoin_char(&lexeme->string, (line[*index]));
		(*index)++;
		if (line[*index] == 36)
		{
			add_token_to_end(&lexeme->head, create_token(lexeme->string));
			lexeme->string = NULL;
			while (line[*index] != 32)
			{
				ft_strjoin_char(&lexeme->string, line[*index]);
				(*index)++;
			}
			add_token_to_end(&lexeme->head, create_token(lexeme->string));
			lexeme->string = NULL;
		}
		if (line[*index] == 34)
		{
			reset_lexer_state(lexeme);
			break ;
		}
	}
	(*index)++;
}

void	handle_dollar(t_lexeme *lexeme, char *line, int *index)
{
	while (lexeme->lexing_state == DOLLAR)
	{
		ft_strjoin_char(&lexeme->string, (line[*index]));
		(*index)++;
		if (line[*index] == 32 || line[*index] == '\0' || line[*index
			- 1] == 63)
		{
			reset_lexer_state(lexeme);
			break ;
		}
	}
}
