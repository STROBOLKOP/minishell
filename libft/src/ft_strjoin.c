/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:52:53 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:16:12 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	len1;
	unsigned int	len2;
	char			*res;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, len1);
	ft_memcpy(&res[len1], s2, len2);
	res[len1 + len2] = 0;
	return (res);
}
//
//#include <stdio.h>
//int	main(void)
//{
//	printf("%s\n", ft_strjoin("We are now", " together"));
//	return (0);
//}
