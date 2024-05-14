/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:37:56 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/14 15:53:45 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void tokenizer(char *line)
{
	t_token *token;

	token = NULL;
	create_token(&token, line);
	printf("The value is: %s\n", token->str);
	printf("The depth is: %d\n", token->depth);
	printf("The tag is: %u\n", token->tag);


}

t_token	*create_token(t_token **head, char *string)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->str = string;
	new_token->depth = 4;
	new_token->tag = str;
	if (!*head)
		*head = new_token;
	return (new_token);

}
/*
void		add_token_to_end(t_token **head, t_token *new_token)
{
	t_token	*iter;

	iter  = *head;
	if (iter->next)
	{
		while (iter->next)
			iter = iter->next;
	}
	iter->next = new_token;
}

void	print_list(t_token **token)
{
	while (token)
	{
		printf("The value in the node is: %s\n", (*token)->str);
		if ((*token)->next)
			*token = (*token)->next;
		else
		 return ;
	}
}*/
