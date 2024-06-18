/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:52:04 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:15:55 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

static char	*ft_alloc_converted(int number, char *base_to, int *res_len)
{
	long	n;
	ssize_t	base_len;
	char	*res;

	n = (long)number;
	base_len = ft_strlen(base_to);
	if (n < 0)
	{
		n = -n;
		*res_len += 1;
	}
	while (n > base_len - 1)
	{
		*res_len += 1;
		n /= base_len;
	}
	res = malloc(sizeof(char) * (*res_len + 2));
	if (!res)
		return (0);
	return (res);
}

char	*ft_itoa_base(int number, char *base)
{
	long	n;
	ssize_t	base_len;
	char	*res;
	int		res_len;
	int		i;

	res_len = 0;
	res = ft_alloc_converted(number, base, &res_len);
	n = (long)number;
	base_len = ft_strlen(base);
	i = 0;
	if (n < 0)
	{
		res[i++] = '-';
		n = -n;
		res_len--;
	}
	while (res_len >= 0)
	{
		res[i] = base[(n / ft_pow(base_len, res_len)) % base_len];
		i++;
		res_len--;
	}
	res[i] = '\0';
	return (res);
}

/*
#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_itoa_base(1234, "0123456789abcdef"));
	return (0);
}
*/
