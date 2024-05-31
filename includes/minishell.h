/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:32:55 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/30 22:26:47 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/incl/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_token_type
{
	CMD,
	PIPE,
	REDIRECT,
	MAKE_VAR,
}	t_token_type;

typedef enum e_lexing_state
{
	START,
	UNQUOTED,
	SQ,
	DQ,
	SP,
	META,
	DOLLAR,
}	t_lexing_state;

/*   STRUCTURES   */
typedef struct s_token
{
	char					*str;
	t_token_type			tag;
	struct s_token			*next;
}							t_token;

typedef struct s_lexeme
{
	char					*string;
	t_token					*head;
	t_lexing_state			lexing_state;
}							t_lexeme;

/* MAIN LOOP */
void	interactive(void);

/*	UTILS	*/
bool	exact_match(char *s, char *to_match);
void	exit_handler(int status);
int		is_regular_character(char c);
int		is_meta_character(char c);
void	reset_lexer_state(t_lexeme *lexeme, t_lexing_state lexing_state);
int		ft_strjoin_char(char **str, char c);
/*	LINKED LIST FUNCTIONS	*/
t_token	*create_token(char *string);
void	add_token_to_end(t_token **head, t_token *new_token);
void	print_list(t_token **token);

/*	SRC	*/
int		check_for_builtins(char *string);
void	tokenizer(char *line);
t_token	*lexer(char *line);
void	handle_single_quotes(t_lexeme *lexeme, char *line, int *index);
void	handle_unquoted(t_lexeme *lexeme, char *line, int *index);
void	update_lexer_state(t_lexeme *lexeme, char *line, int *index);
void	handle_meta_char(t_lexeme *lexeme, char *line, int *index);
void	handle_space(t_lexeme *lexeme, char *line, int *index);
void	handle_double_quotes(t_lexeme *lexeme, char *line, int *index);
void	handle_dollar(t_lexeme *lexeme, char *line, int *index);
void	parser(t_token **token);

#endif
