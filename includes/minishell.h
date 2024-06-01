/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:32:55 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/31 22:29:28 by elias            ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/wait.h>

#define PIPE_R 0
#define PIPE_W 1

typedef enum e_token_type
{
	CMD,
	PIPE,
	REDIRECT,
	MAKE_VAR,
}	t_token_type;

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_APND,
	R_HERE,
}	t_redir_type;

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
	char			*str;
	t_token_type	tag;
	struct s_token	*next;
}	t_token;

typedef struct s_lexeme
{
	char			*string;
	t_token			*head;
	t_lexing_state	lexing_state;
}	t_lexeme;

typedef struct s_redir
{
	char			*str;
	int				flags;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**cmd_av;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

/* MAIN LOOP */
void	interactive(char **envp); //probably just have argument be the t_minishell struct

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
t_cmd	*create_cmd(char **cmd_av, t_redir *redirs);
void	cmd_add_back(t_cmd **head, t_cmd *new_node);
t_redir	*create_redir(char *str, int flags);
void	redir_add_back(t_redir **head, t_redir *new_node);
void	free_tokens(t_token **tokens);

/* COMMANDS */
size_t	count_cmd_av(t_token *tokens);
void	make_cmd_list(t_cmd **cmds, t_token *tokens);
void	free_cmds(t_cmd **cmds);
void	ft_run_cmds(t_cmd *cmds, char **envp);

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
