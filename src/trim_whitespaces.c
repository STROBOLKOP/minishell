/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_whitespaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:26:43 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/13 18:07:30 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*trim_whitespaces(char *line)
{
	char	*trimmed_line;
	int		iter_old;
	int		iter_new;

	iter_old = 0;
	iter_new = 0;
	trimmed_line = malloc(ft_strlen_whitespace(line) * sizeof(char) + 1);
	if (!trimmed_line)
		return (NULL);
	while (line[iter_old])
	{
		if ((line[iter_old] == 32 && line[iter_old - 1] == 32) || (iter_old == 0
				&& line[iter_old] == 32))
			iter_old++;
		else
		{
			trimmed_line[iter_new] = line[iter_old];
			iter_new++;
			iter_old++;
		}
	}
	trimmed_line[iter_new] = '\0';
	free(line);
	return (trimmed_line);
}

int	ft_strlen_whitespace(char *string)
{
	int	len;
	int	iter;

	len = 0;
	iter = 0;
	while (string[iter])
	{
		if ((string[iter] == 32 && string[iter - 1] == 32) || (iter == 0
				&& string[iter] == 32))
			iter++;
		else
		{
			len++;
			iter++;
		}
	}
	return (len);
}
