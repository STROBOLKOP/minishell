/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:09:58 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/31 00:00:20 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parser(t_token **token)
{
	t_token	*iter;

	if (!token)
		return ;
	iter = *token;
	while (iter && iter->str != NULL)
	{
		if ((ft_strnstr(iter->str, "|", 1) != NULL))
			iter->tag = PIPE;
		else if ((ft_strnstr(iter->str, "<", 1) != NULL)
				|| (ft_strnstr(iter->str, ">", 1) != NULL)
				|| (ft_strnstr(iter->str, "<<", 2) != NULL)
				|| (ft_strnstr(iter->str, ">>", 2) != NULL)
				|| (ft_strnstr(iter->str, "END", 3) != NULL))
			iter->tag = REDIRECT;
		else if ((ft_strnstr(iter->str, "VAR=", 4)))
			iter->tag = MAKE_VAR;
		else
			iter->tag = CMD;
		iter = iter->next;
	}
}
