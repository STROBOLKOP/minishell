/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:37:56 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/22 18:21:08 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tokenizer(char *line)
{
	t_token	*head;

	head = NULL;
	add_token_to_end(&head, create_token(line));
	printf("test\n");
	print_list(&head);	
}

t_token	*create_token(char *string)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->str = string;
	new_token->depth = 4;
	new_token->tag = str;
	new_token->next = NULL;
	return (new_token);
}

void	add_token_to_end(t_token **head, t_token *new_token)
{
	t_token	*iter;

	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	iter = *head;
	while (iter->next != NULL)
		iter = iter->next;
	iter->next = new_token;
}

void	print_list(t_token **token)
{
	int iter;

	iter = 0;
	while (token != NULL && (*token)->str != NULL)
	{
		printf("#%d: The value in the node from the tokenizer is: %s\n", iter, (*token)->str);
		iter++;
		if ((*token)->next != NULL)
			*token = (*token)->next;
		else
		 break ;
	}
}
