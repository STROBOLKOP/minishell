/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_free_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 21:07:08 by efret             #+#    #+#             */
/*   Updated: 2024/05/31 21:41:37 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_redirs(t_redir **redirs)
{
	t_redir	*free_me;

	if (!redirs || !(*redirs))
		return ;
	free_me = *redirs;
	while (*redirs)
	{
		*redirs = (*redirs)->next;
		free(free_me);
		free_me = *redirs;
	}
}

void	free_cmds(t_cmd **cmds)
{
	t_cmd	*free_me;

	if (!cmds || !(*cmds))
		return ;
	free_me = *cmds;
	while (*cmds)
	{
		*cmds = (*cmds)->next;
		free_redirs(&free_me->redirs);
		free(free_me->cmd_av);
		free(free_me);
		free_me = *cmds;
	}
}
