/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 09:23:16 by pclaus            #+#    #+#             */
/*   Updated: 2024/07/08 15:57:37 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_quotes_from_quoted_string(t_token **token)
{
	t_token	*iter;
	char	*trimmed_string;

	iter = *token;
	while (iter)
	{
		if (iter->str[0] == '\'' && iter->str[ft_strlen(iter->str) - 1] == '\'')
		{
			trimmed_string = ft_strtrim(iter->str, "'");
			free(iter->str);
			iter->str = trimmed_string;
		}
		else if (iter->str[0] == '"' && iter->str[ft_strlen(iter->str) - 1])
		{
			trimmed_string = ft_strtrim(iter->str, "\"");
			free(iter->str);
			iter->str = trimmed_string;
		}
		if (iter->next)
			iter = iter->next;
		else
			break ;
	}
}

void	remove_quotes_from_variables(t_token **token)
{
	t_token	*iter;
	int	str_iter;
	char	*trimmed_string;
	int	len;

	iter = *token;
	while (iter)
	{
		if (ft_strchr(iter->str, '\'') || ft_strchr(iter->str, '"'))
		{
			str_iter = 0;
			while (iter->str[str_iter] != '\0')
			{
				if(iter->str[str_iter] == '=' && (iter->str[str_iter + 1] == '\'' || iter->str[str_iter + 1] == '"'))
				{
					len = ft_strlen(iter->str) - 2;
					trimmed_string = malloc(len * sizeof(char *));
					if (!trimmed_string)
						return ; //failed malloc
					ft_memcpy(trimmed_string, iter->str, str_iter + 1);
					ft_memcpy(trimmed_string + ft_strlen(trimmed_string), iter->str +str_iter + 2, ft_strlen(iter->str) - str_iter - 3);
					free(iter->str);
					iter->str = trimmed_string;

				}
				str_iter++;
			}
		}
		if (iter->next)
			iter = iter->next;
		else
			break ;
	}
}

/*
void	remove_quotes(t_token **token)
{

}
*/
