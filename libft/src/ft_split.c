/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:45:22 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:16:09 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

static unsigned int	ft_count_words(const char *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] && (s[i] != c))
			count++;
		while (s[i] && (s[i] != c))
			i++;
		while (s[i] && (s[i] == c))
			i++;
	}
	return (count);
}

static void	*ft_free_split(char **split, size_t end)
{
	size_t	i;

	i = 0;
	while (i < end)
		free(split[i++]);
	free(split);
	return (NULL);
}

static size_t	ft_fill_split(const char *s, char **word, char c, size_t *i)
{
	size_t	w_len;

	w_len = 0;
	while (s[w_len] && s[w_len] != c)
		w_len++;
	*word = ft_substr(s, 0, w_len);
	if (!(*word))
		return (0);
	*i += w_len;
	return (w_len);
}

char	**ft_split(char const *s, char c)
{
	size_t	w_count;
	size_t	i;
	size_t	w_idx;
	char	**res;

	w_count = ft_count_words(s, c);
	res = malloc(sizeof(char *) * (w_count + 1));
	if (!res)
		return (NULL);
	i = 0;
	w_idx = 0;
	while (s[i] && w_idx < w_count)
	{
		while (s[i] && (s[i] == c))
			i++;
		if (!ft_fill_split(&s[i], &res[w_idx++], c, &i))
			return (ft_free_split(res, w_idx - 1));
	}
	res[w_idx] = 0;
	return (res);
}

//#include <stdio.h>
//int	main(void)
//{
//	char	*s = "   split me please   ";
//	char	c = ' ';
//	char	**split = ft_split(s, c);
//	for (size_t i = 0; split[i]; i++)
//		printf("%s\n", split[i]);
//	ft_free_split(split, ft_count_words(s, c));
//	return (0);
//}

//char	**ft_split(char const *s, char c)
//{
//	unsigned int	w_count;
//	unsigned int	i;
//	unsigned int	w_idx;
//	unsigned int	w_len;
//	char			**res;
//
//	w_count = ft_count_words(s, c);
//	res = malloc(sizeof(char *) * (w_count + 1));
//	if (!res)
//		return (NULL);
//	i = 0;
//	w_idx = 0;
//	while (s[i] && w_idx < w_count)
//	{
//		w_len = 0;
//		while (s[i + w_len] && (s[i + w_len] != c))
//			w_len++;
//		if (w_len)
//			res[w_idx++] = ft_substr(s, i, w_len);
//		i += w_len;
//		while (s[i] && (s[i] == c))
//			i++;
//	}
//	res[w_idx] = 0;
//	return (res);
//}
