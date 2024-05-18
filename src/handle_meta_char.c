/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_meta_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 21:31:35 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/18 21:38:13 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_meta_character(char c)
{
	if (c == 124 || c == 38 || c == 59 || c == 40 || c == 41 || c == 60
		|| c == 61 || c == '\0')
		return (0);
	else
		return (1);
}

int	is_double_meta_character(char c)
{
	if ((c == 124 && c - 1 == 124) || (c == 38 && c - 1 == 38) || (c == 59 && c
			- 1 == 59) || (c == 40 && c - 1 == 40) || (c == 41 && c - 1 == 41)
		|| (c == 60 && c - 1 == 60) || (c == 62 && c - 1 == 62))
		return (0);
	else
		return (1);
}

void	handle_meta_char(t_lexeme *lexeme, char *line, int *index)
{
	while (lexeme->lexing_state == META)
	{
		if (line[*index] == 32)
		{
			(*index)++;
			lexeme->lexing_state = START;
			lexeme->string = NULL;
			break ;
		}
		ft_strjoin_char(&lexeme->string, (line[*index]));
		(*index)++;
		if (is_meta_character(line[*index]))
		{
			if (is_double_meta_character(line[*index]) == 0)
				break ;
			lexeme->lexing_state = START;
			add_token_to_end(&lexeme->head, create_token(lexeme->string));
			lexeme->string = NULL;
			break ;
		}
	}
}
