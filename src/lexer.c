/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:56:40 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/15 20:50:08 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer(char *line)
{
	static size_t index;
	char	*string;
	
	index = 0;
	string = NULL;
	while (line && line[index])
	{
		if (line[index] == 39)
		{
			printf("The zero test is: %c\n", line[index]);
			index++;
			printf("The first test is: %c\n", line[index]);
			while (line[index] != 39)
			{
				printf("The second test is: %c\n", line[index]);
				ft_strjoin_char(&string, line[index]);
				index++;
			}
			index++;
			continue ;
		}
		
		if (line[index] == 32 || line[index] == 9 || line[index] == 10)
		{
			
			index++;
		}
		else if ((line[index] >= 'a' && line[index] <= 'z') || (line[index] >= 'A' || line[index] <= 'Z'))
			ft_strjoin_char(&string, line[index++]);		
		printf("The string from the lexer is: %s\n", string);
		
		tokenizer(string);
	}

}
