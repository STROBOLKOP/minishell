/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:30:39 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:16:22 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

static size_t	ft_utoa_len(unsigned int n)
{
	size_t	len;
	long	num;

	num = (long)n;
	len = 1;
	while (num > 9)
	{
		len++;
		num /= 10;
	}
	return (len);
}

char	*ft_utoa(unsigned int n)
{
	size_t	len;
	size_t	i;
	long	num;
	char	*res;

	len = ft_utoa_len(n);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	num = (long)n;
	while (len-- > 0)
		res[i++] = "0123456789"[(num / ft_pow(10, len)) % 10];
	res[i] = 0;
	return (res);
}
