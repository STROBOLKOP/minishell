/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_make_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elias <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:36:12 by elias             #+#    #+#             */
/*   Updated: 2024/06/05 10:58:32 by elias            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env(t_var *head)
{
	while (head)
	{
		printf("%sNAME:\t%s\n%sVALUE:\t%s%s\n", "\033[33m", head->name, "\033[32m", head->value, "\033[0m");
		head = head->next;
	}
}

void	env_add_var(t_var **head, char *token)
{
	char	*name;
	char	*val;
	char	*equal_sign;
	t_var	*node;

	//should search first, so its value should be changed
	name = strdup(token);
	if (!name)
		return (errno = ENOMEM, (void)0);
	equal_sign = strchr(name, '=');
	val = equal_sign + 1;
	*equal_sign = '\0';
	if (*val == '\0')
		val = NULL;
	node = create_env_var(name, val, false);
	if (!node)
		exit(1); //Error handling
	env_add_back(head, node);
}

void	env_load(t_var **head, char **envp)
{
	char	*name;
	char	*val;
	char	*equal_sign;
	t_var	*node;

	while (*envp)
	{
		name = strdup(*envp); //maybe we don't even need to dupe.
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
