/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_make_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:36:12 by elias             #+#    #+#             */
/*   Updated: 2024/06/13 13:28:29 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static inline t_var	*is_node(t_var *node)
{
	if (node)
		return (node);
	return (NULL);
}

void	print_env(t_var *head)
{
	while (head)
	{
		printf("%sNAME:\t%s\n%sVALUE:\t%s%s\n", "\033[33m", head->name, "\033[32m", head->value, "\033[0m");
		head = head->next;
	}
}

t_var	*env_add_var(t_var **head, char *token, t_var *node)
{
	char	*name;
	char	*val;
	char	*equal_sign;

	name = ft_strdup(token);
	if (!name)
		return (errno = ENOMEM, NULL);
	equal_sign = strchr(name, '=');
	if (!equal_sign)
		return (free(name), NULL);
	val = equal_sign + 1;
	*equal_sign = '\0';
	node = env_search_name(*head, name);
	if (node)
	{
		free(node->name);
		node->name = name;
		node->value = val;
		return (node);
	}
	if (*val == '\0')
		val = NULL;
	node = create_env_var(name, val, false);
	env_add_back(head, node);
	return (is_node(node));
}

void	env_load(t_var **head, char **envp)
{
	char	*name;
	char	*val;
	char	*equal_sign;
	t_var	*node;

	while (*envp)
	{
		name = ft_strdup(*envp); //maybe we don't even need to dupe.
		if (!name)
			return (errno = ENOMEM, (void)0);
		equal_sign = strchr(name, '=');
		val = equal_sign + 1;
		*equal_sign = '\0';
		if (*val == '\0')
			val = NULL; // should we set it to NULL or just leave it as '\0'?
		node = create_env_var(name, val, true);
		if (!node)
			exit(1); //Error handling.
		env_add_back(head, node);
		envp++;
	}
}
