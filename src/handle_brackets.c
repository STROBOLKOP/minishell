/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_brackets.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:01:19 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/23 17:48:44 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void	handle_square_brackets(t_lexeme *lexeme, char *line, int *index)
{
	while (line && line[*index] != '\0' && line[*index] == 91)
	{
		ft_strjoin_char(&lexeme->string, line[*index]);
		(*index)++;
		if (handle_unexpected_token(line, *index, 91))
			exit(1);
		if (line[*index] != 91)
		{
			reset_lexer_state(lexeme, START);
			break ;
		}
	}
	while (line && line[*index] != '\0' && line[*index] == 93)
	{
		ft_strjoin_char(&lexeme->string, line[*index]);
		(*index)++;
		if (handle_unexpected_token(line, *index, 93))
			exit(1);
		if (line[*index] != 93)
		{
			reset_lexer_state(lexeme, START);
			break ;
		}
	}
}
/*
void	handle_curly_brackets(t_lexeme *lexeme, char *line, int *index)
{
	while (line && line[*index] != '\0' && line[*index] == 123)
	{
		ft_strjoin_char(&lexeme->string, line[*index]);
		(*index)++;
		if (handle_unexpected_token(line, *index, 123))
			exit(1);
		if (line[*index] != 123)
		{
			reset_lexer_state(lexeme, START);
			break ;
		}
	}
	while (line && line[*index] != '\0' && line[*index] == 125)
	{
		ft_strjoin_char(&lexeme->string, line[*index]);
		(*index)++;
		if (handle_unexpected_token(line, *index, 125))
			exit(1);
		if (line[*index] != 125)
		{
			reset_lexer_state(lexeme, START);
			break ;
		}
	}
}
*/
void	handle_single_curly_brackets(t_lexeme *lexeme, char *line, int *index)
{
	while (lexeme->lexing_state == LCBRACKET || lexeme->lexing_state == RCBRACKET)
	{
		ft_strjoin_char(&lexeme->string, line[*index]);
		(*index)++;
		if (line[*index] == 125)
		{
			ft_strjoin_char(&lexeme->string, line[*index]);
			reset_lexer_state(lexeme, START);
		}
	}
	(*index)++;
}

/*
void	handle_parentheses(t_lexeme *lexeme, char *line, int *index)
{
	while (line && line[*index] != '\0' && line[*index] == 40)
	{
		ft_strjoin_char(&lexeme->string, line[*index]);
		(*index)++;
		if (handle_unexpected_token(line, *index, 40))
			exit(1);
		if (line[*index] != 40)
		{
			reset_lexer_state(lexeme, START);
			break ;
		}
	}
	while (line && line[*index] != '\0' && line[*index] == 41)
	{
		ft_strjoin_char(&lexeme->string, line[*index]);
		(*index)++;
		if (handle_unexpected_token(line, *index, 40))
			exit(1);
		if (line[*index] != 41)
		{
			reset_lexer_state(lexeme, START);
			break ;
		}
	}
}
*/
void	handle_single_parentheses(t_lexeme *lexeme, char *line, int *index)
{
	while (lexeme->lexing_state == LPAR || lexeme->lexing_state == RPAR)
	{
		if (line[*index] == 40 && line[*index + 1] != 40)
		{
			ft_strjoin_char(&lexeme->string, line[*index]);
			add_token_to_end(&lexeme->head, create_token(lexeme->string));
			lexeme->string = NULL;
			(*index)++;
		}
		ft_strjoin_char(&lexeme->string, line[*index]);
		(*index)++;
		if (line[*index + 1] == 41)
		{
			ft_strjoin_char(&lexeme->string, line[*index]);
			reset_lexer_state(lexeme, RPAR);
			(*index)++;
		}
		if (line[*index] == 41)
		{
			ft_strjoin_char(&lexeme->string, line[*index]);
			reset_lexer_state(lexeme, START);
		}
	}
	(*index)++;
}
