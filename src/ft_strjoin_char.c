/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:15:29 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/15 14:48:32 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strjoin_char(char **str, char c)
{
	char	*tmp;
	char	*new_str;
	size_t	i;

	if (!str)
		return (1);
	new_str = malloc(sizeof(ft_strlen(*str) + 2));
	if (!new_str)
		return (1);
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
