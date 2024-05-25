/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:32:55 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/25 10:16:27 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum token_type		t_token_type;

enum						token_type
{
	str,
	nb
};

typedef enum s_lexing_state	t_lexing_state;

enum						s_lexing_state
{
	START,
	UNQUOTED,
	SQ,
	DQ,
	SP,
	META,
	DOLLAR,
	LBRACKET,
	RBRACKET,
	LCBRACKET,
	RCBRACKET,
	LPAR,
	RPAR,
};

/*   STRUCTURES   */
typedef struct s_token
{
	char					*str;
	int						depth;
	t_token_type			tag;
	struct s_token			*next;
}							t_token;

typedef struct s_lexeme
{
	char					*string;
	t_token					*head;
	t_lexing_state			lexing_state;
}							t_lexeme;

/*	UTILS	*/
size_t						ft_strlen(const char *s);
bool						exact_match(char *s, char *to_match);
void						exit_handler(int status);
int							ft_strlen_whitespace(char *string);
char						*trim_whitespaces(char *line);
t_token						*create_token(char *string);
void	add_token_to_end(t_token **head,
						t_token *new_token);
void						print_list(t_token **token);
int							ft_strjoin_char(char **str, char c);
int							is_meta_character(char c);
int							is_regular_character(char c);
void						update_lexer_state(t_lexeme *lexeme, char *line,
								int *index);
void	reset_lexer_state(t_lexeme *lexeme,
						t_lexing_state lexing_state);
int							handle_unexpected_token(char *line, int index,
								char ascii_code);
void						free_list(t_token **token);

/*	SRC	*/
int							check_for_builtins(char *string);
void						tokenizer(char *line);
void						lexer(char *line);
void						handle_single_quotes(t_lexeme *lexeme, char *line,
								int *index);
void						handle_unquoted(t_lexeme *lexeme, char *line,
								int *index);
void						update_lexer_state(t_lexeme *lexeme, char *line,
								int *index);
void						handle_meta_char(t_lexeme *lexeme, char *line,
								int *index);
void						handle_space(t_lexeme *lexeme, char *line,
								int *index);
void						handle_double_quotes(t_lexeme *lexeme, char *line,
								int *index);
void						handle_dollar(t_lexeme *lexeme, char *line,
								int *index);
/*	BUILTINS	*/
void						env_builtin(void);
void						cd_builtin(void);
void						pwd_builtin(void);

#endif
