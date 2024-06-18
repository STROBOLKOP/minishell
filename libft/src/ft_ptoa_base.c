/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:07:43 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:16:06 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

static char	*ft_alloc_converted(uintptr_t addr, char *base_to, int *res_len)
{
	size_t		base_len;
	char		*res;

	*res_len = 1;
	base_len = ft_strlen(base_to);
	while (addr > base_len -1)
	{
		*res_len += 1;
		addr /= base_len;
	}
	res = malloc(sizeof(char) * (*res_len + 1));
	if (!res)
		return (0);
	return (res);
}

char	*ft_ptoa_base(uintptr_t addr, char *base)
{
	ssize_t	base_len;
	char	*res;
	int		res_len;

	res_len = 0;
	res = ft_alloc_converted(addr, base, &res_len);
	base_len = ft_strlen(base);
	res[res_len] = '\0';
	while (res_len-- > 0)
	{
		res[res_len] = base[addr % base_len];
		addr /= base_len;
	}
	return (res);
}
