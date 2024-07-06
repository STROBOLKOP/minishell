/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:56:40 by pclaus            #+#    #+#             */
/*   Updated: 2024/07/06 21:25:33 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*lexer(char *line)
{
	t_lexeme	lexeme;
	int	index;

	index = 0;
	lexeme.lexing_state = START;
	lexeme.string = NULL;
	lexeme.head = NULL;
	while (line && line[index])
	{
		update_lexer_state(&lexeme, line, &index);
		if (lexeme.lexing_state == UNQUOTED)
			handle_unquoted(&lexeme, line, &index);
		else if (lexeme.lexing_state == SQ)
			handle_single_quotes(&lexeme, line, &index);
		else if (lexeme.lexing_state == DQ)
			handle_double_quotes(&lexeme, line, &index);
		else if (lexeme.lexing_state == META)
			handle_meta_char(&lexeme, line, &index);
		else if (lexeme.lexing_state == SP)
			handle_space(&lexeme, line, &index);
		else if (lexeme.lexing_state == DOLLAR)
			handle_dollar(&lexeme, line, &index);
		else if (lexeme.lexing_state == START)
			break ;
		else
		 	exit_handler(1);
	}
	parser(&lexeme.head);
//	free_list(&lexeme.head);
//	print_list(&lexeme.head);
	return (lexeme.head);
}

t_token	*next_token(char *str)
{
	t_token			*tok;
	static size_t	i = 0;
	bool			quote;

	if (!str)
		return (i = 0, NULL);
	if (!str[i])
		return (NULL);
	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (NULL);
	quote = false;
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == ' '))
		i++;
	while (str[i] && (quote || !(str[i] == '\t' || str[i] == '\n' || str[i] == ' ')))
	{
		if (str[i] == '\'' || str[i] == '\"')
			quote = !quote;
		ft_strjoin_char(&tok->str, str[i++]);
	}
	return (tok);
}

t_token	*test_lexer(char *line)
{
	t_token	*token;
	t_token	*ret_tokens;

	ret_tokens = NULL;
	token = next_token(line);
	while (token)
	{
		add_token_to_end(&ret_tokens, token);
		token = next_token(line);
	}
	next_token(NULL);
	return (ret_tokens);
}
