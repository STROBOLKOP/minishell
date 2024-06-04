/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:39:36 by elias             #+#    #+#             */
/*   Updated: 2024/06/04 16:40:37 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_var	*create_env_var(char *name, char *val, bool is_exp)
{
	t_env_var *var;

	var = malloc(sizeof(t_env_var));
	if (var)
		*var = (t_env_var){name, val, is_exp, NULL, NULL};
	return (var);
}

void	env_add_back(t_env_var **head, t_env_var *new_node)
{
	t_env_var	*iter;

	if (!head)
		return (errno = EINVAL, (void)0);
	if (!(*head))
		return (*head = new_node, (void)0);
	iter = *head;
	while (iter->next)
		iter = iter->next;
	iter->next = new_node;
	new_node->prev = iter;
}

void	env_del_target(t_env_var **head, t_env_var *node)
{
	t_env_var	*next;
	t_env_var	*prev;

	if (!node)
		return ;
	prev = node->prev;
	next = node->next;
	if (next)
		next->prev = prev;
	if (prev)
		prev->next = next;
	else
		*head = next;
	free(node->name);
	free(node);
}

t_env_var	*env_search_name(t_env_var *head, char *name)
{
	t_env_var	*iter;

	if (!name)
		return (NULL);
	iter = head;
	while (iter && !exact_match(iter->name, name))
		iter = iter->next;
	return (iter);
}
