/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:04:43 by elias             #+#    #+#             */
/*   Updated: 2024/05/13 15:18:06 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum e_ast_tag		t_ast_tag ;

enum e_ast_tag
{
	AST_ADD,
	AST_MUL,
	AST_NBR,
	AST_END
};

typedef struct s_ast_token
{
	char				*str;
	int					depth;
	t_ast_tag			tag;
	struct s_ast_token	*next;
}	t_ast_token;

t_ast_token	*new_token_node(char *str, int depth, t_ast_tag tag)
{
	t_ast_token	*new_node;

	new_node = malloc(sizeof(t_ast_token));
	if (!new_node)
		return (NULL);
	new_node->str = str;
	new_node->depth = depth;
	new_node->tag = tag;
	new_node->next = NULL;
	return (new_node);
}

void	token_add_back(t_ast_token **token, t_ast_token *new_node)
{
	t_ast_token	*iter;

	if (*token == NULL && new_node)
	{
		*token = new_node;
		return ;
	}
	iter = *token;
	while (iter->next)
		iter = iter->next;
	iter->next = new_node;
}

void	free_tokens(t_ast_token **token)
{
	t_ast_token	*temp;

	while (*token)
	{
		temp = (*token)->next;
		free((*token)->str);
		free(*token);
		*token = temp;
	}
	*token = NULL;
}

void	print_tokens(t_ast_token *token)
{
	printf("(nbr, depth, tag):");
	printf("\n\t");
	while (token)
	{
		printf("(\"%s\", %d, %d)", token->str, token->depth, token->tag);
		if (token->next)
			printf(" -> \n\t");
		token = token->next;
	}
	printf("\n");
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (str)
		while (str[len])
			len++;
	return (len);
}

int	ft_strjoinc(char **str, char c)
{
	char	*tmp;
	char	*new_str;
	size_t	i;

	if (!str)
		return (EXIT_FAILURE);
	new_str = malloc(ft_strlen(*str) + 2);
	i = 0;
	if (*str)
		while ((*str)[i])
			(new_str[i] = (*str)[i], i++);
	new_str[i] = c;
	new_str[i + 1] = '\0';
	tmp = *str;
	*str = new_str;
	free(tmp);
	return (0);
}

char	*next_token(char *str)
{
	char			*tok;
	static size_t	i = 0;
	int				par;

	par = 0;
	tok = NULL;
	if (!str)
		return (errno = EINVAL, NULL);
	if (!str[i])
		return (NULL);
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == ' '))
		i++;
	if (str[i] == '(')
	{
		par++;
		while (str[i] && par)
		{
			ft_strjoinc(&tok, str[i]);
			if (str[i] == ')')
				par += 1 - 2 * (str[i] == ')');
			i++;
		}
	}
	else
		while (str[i] && !(str[i] == '\t' || str[i] == '\n' || str[i] == ' '))
			ft_strjoinc(&tok, str[i++]);
	return (tok);
}

int	main(int ac, char **av)
{
	char		*token_val;
	t_ast_token	*token;
	token = NULL;
	token_val = NULL;

	/*
	// "4 + 3 * (2 + 1)"
	token_add_back(&token, new_token_node("4", 1, AST_NBR));
	token_add_back(&token, new_token_node("+", 0, AST_ADD));
	token_add_back(&token, new_token_node("3", 2, AST_NBR));
	token_add_back(&token, new_token_node("*", 1, AST_MUL));
	token_add_back(&token, new_token_node("1", 3, AST_NBR));
	token_add_back(&token, new_token_node("+", 2, AST_ADD));
	token_add_back(&token, new_token_node("2", 3, AST_NBR));
	*/

	/*
	// "(4 + 3) * (2 + 1)"
	token_add_back(&token, new_token_node("4", 2, AST_NBR));
	token_add_back(&token, new_token_node("+", 1, AST_ADD));
	token_add_back(&token, new_token_node("3", 2, AST_NBR));
	token_add_back(&token, new_token_node("*", 0, AST_MUL));
	token_add_back(&token, new_token_node("2", 2, AST_NBR));
	token_add_back(&token, new_token_node("+", 1, AST_ADD));
	token_add_back(&token, new_token_node("1", 2, AST_NBR));
	*/

	/*
	// "((8 * 3) + (1 + 4 * 5)) * (6 * 5 * 2) + 4
	token_add_back(&token, new_token_node("8", 4, AST_NBR));
	token_add_back(&token, new_token_node("*", 3, AST_MUL));
	token_add_back(&token, new_token_node("3", 4, AST_NBR));
	token_add_back(&token, new_token_node("+", 2, AST_ADD));
	token_add_back(&token, new_token_node("1", 4, AST_NBR));
	token_add_back(&token, new_token_node("+", 3, AST_ADD));
	token_add_back(&token, new_token_node("4", 5, AST_NBR));
	token_add_back(&token, new_token_node("*", 4, AST_MUL));
	token_add_back(&token, new_token_node("5", 5, AST_NBR));
	token_add_back(&token, new_token_node("*", 1, AST_MUL));
	token_add_back(&token, new_token_node("6", 3, AST_NBR));
	token_add_back(&token, new_token_node("*", 2, AST_MUL));
	token_add_back(&token, new_token_node("5", 4, AST_NBR));
	token_add_back(&token, new_token_node("*", 3, AST_MUL));
	token_add_back(&token, new_token_node("2", 4, AST_NBR));
	token_add_back(&token, new_token_node("+", 0, AST_ADD));
	token_add_back(&token, new_token_node("4", 1, AST_NBR));
	*/

	if (ac != 2)
		return (0);
	token_val = next_token(av[1]);
	while (token_val)
	{
		token_add_back(&token, new_token_node(token_val, 0, AST_END));
		token_val = next_token(av[1]);
	}
	print_tokens(token);
	free_tokens(&token);
	return (0);
}
