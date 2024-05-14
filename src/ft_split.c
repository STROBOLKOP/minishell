/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pclaus <pclaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:04:27 by pclaus            #+#    #+#             */
/*   Updated: 2024/05/14 15:05:26 by pclaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	number_of_substrings(char *s, char c)
{
	int	in_word;
	int	count;

	in_word = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*get_word(char *s, char c)
{
	static int	cursor = 0;
	char		*word;
	int			len;
	int			index;

	len = 0;
	index = 0;
	while (s[cursor] == c)
		cursor++;
	while ((s[cursor + len] != c) && s[cursor + len])
		len++;
	word = malloc(len * sizeof(char) + 1);
	if (!word)
		return (NULL);
	while ((s[cursor] != c) && s[cursor])
		word[index++] = s[cursor++];
	word[index] = '\0';
	return (word);
}

char	**ft_split(char *str, char separator)
{
	char	**vector_strings;
	int		number_of_words;
	int		index;

	index = 0;
	number_of_words = number_of_substrings(str, separator);
	vector_strings = malloc(sizeof(char *) * (number_of_words + 2));
	if (!vector_strings)
		return (NULL);
	while (number_of_words-- >= 0)
	{
		if (index == 0)
		{
			vector_strings[index] = malloc(sizeof(char));
			if (!vector_strings[index])
				return (NULL);
			vector_strings[index++][0] = '\0';
			continue ;
		}
		vector_strings[index++] = get_word(str, separator);
	}
	vector_strings[index] = NULL;
	return (vector_strings);
}
