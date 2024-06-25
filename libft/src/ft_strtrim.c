/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:17:29 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:16:19 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

static int	ft_c_in_str(const char *s, int c)
{
	c = (char)c;
	while (*s)
		if (*(s++) == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	end;
	char			*res;

	end = ft_strlen(s1);
	while (end > 0 && ft_c_in_str(set, s1[end - 1]))
		end--;
	i = 0;
	while (i < end && ft_c_in_str(set, s1[i]))
		i++;
	if (i == end)
		return (ft_calloc(1, 1));
	res = malloc(sizeof(char) * (end - i + 1));
	if (!res)
		return (NULL);
	ft_memcpy(res, &s1[i], end - i);
	res[end - i] = 0;
	return (res);
}
