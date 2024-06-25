/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:38:11 by efret             #+#    #+#             */
/*   Updated: 2024/06/09 21:12:08 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*create_cmd(char **cmd_av, t_redir *redirs)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd)
		*cmd = (t_cmd){cmd_av, redirs, NULL};
	return (cmd);
}

void	cmd_add_back(t_cmd **head, t_cmd *new_node)
{
	t_cmd	*iter;

	if (!head)
		return (errno = EINVAL, (void)0);
	if (!(*head))
		return (*head = new_node, (void)0);
	iter = *head;
	while (iter->next)
		iter = iter->next;
	iter->next = new_node;
}

t_redir	*create_redir(char *str, int flags)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (redir)
		*redir = (t_redir){str, -1, flags, false, NULL};
	return (redir);
}

void	redir_add_back(t_redir **head, t_redir *new_node)
{
	t_redir	*iter;

	if (!head)
		return (errno = EINVAL, (void)0);
	if (!(*head))
		return (*head = new_node, (void)0);
	iter = *head;
	while (iter->next)
		iter = iter->next;
	iter->next = new_node;
}
