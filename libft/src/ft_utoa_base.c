/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:57:59 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:16:23 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

static char	*ft_alloc_converted(unsigned int number,
		char *base_to, int	*res_len)
{
	ssize_t		base_len;
	char		*res;

	base_len = ft_strlen(base_to);
	while (number > base_len -1)
	{
		*res_len += 1;
		number /= base_len;
	}
	res = malloc(sizeof(char) * (*res_len + 2));
	if (!res)
		return (0);
	return (res);
}

char	*ft_utoa_base(unsigned int number, char *base)
{
	ssize_t	base_len;
	char	*res;
	int		res_len;
	int		i;

	res_len = 0;
	res = ft_alloc_converted(number, base, &res_len);
	base_len = ft_strlen(base);
	i = 0;
	while (res_len >= 0)
	{
		res[i] = base[(number / ft_pow(base_len, res_len)) % base_len];
		i++;
		res_len--;
	}
	res[i] = '\0';
	return (res);
}
