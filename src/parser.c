/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:09:58 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/29 19:06:01 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parser(t_token **token)
{
	while ((*token)->str != NULL && token != NULL)
	{
		if ((ft_strnstr((*token)->str, "|", 1) != NULL))
			(*token)->tag = PIPE;
		else if ((ft_strnstr((*token)->str, "<", 1) != NULL)
				|| (ft_strnstr((*token)->str, ">", 1) != NULL)
				|| (ft_strnstr((*token)->str, "<<", 2) != NULL)
				|| (ft_strnstr((*token)->str, ">>", 2) != NULL)
				|| (ft_strnstr((*token)->str, "END", 3) != NULL))
			(*token)->tag = REDIRECT;
		else if ((ft_strnstr((*token)->str, "VAR=", 4)))
			(*token)->tag = MAKE_VAR;
		else
			(*token)->tag = CMD;
		if ((*token)->next)
			*token = (*token)->next;
		else
			break ;
	}
}
