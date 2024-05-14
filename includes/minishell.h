/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:32:55 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/14 15:53:01 by pclaus           ###   ########.fr       */
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

typedef enum token_type      t_token_type;

enum token_type {
    str,
    nb 
};

/*   STRUCTURES   */
typedef struct s_token
{
	char				*str;
	int					depth;
	t_token_type			tag;
	struct s_token	*next;
}	t_token;


/*	UTILS	*/
size_t	ft_strlen(const char *s);
bool	exact_match(char *s, char *to_match);
void	exit_handler(int status);
int		ft_strlen_whitespace(char *string);
char	*trim_whitespaces(char *line);
t_token	*create_token(t_token **head, char *string);
void		add_token_to_end(t_token **head, t_token *new_token);

/*	SRC	*/
int		check_for_builtins(char *string);
void	tokenizer(char *line);

/*	BUILTINS	*/
void	env_builtin(void);
void	cd_builtin(void);
void	pwd_builtin(void);

#endif
