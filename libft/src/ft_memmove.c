/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:26:06 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:16:03 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dptr;
	unsigned char	*sptr;

	if (!dest && !src && n)
		return (NULL);
	dptr = (unsigned char *)dest;
	sptr = (unsigned char *)src;
	if (dest > src)
	{
		i = n;
		while (i-- > 0)
			dptr[i] = sptr[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			dptr[i] = sptr[i];
			i++;
		}
	}
	return (dest);
}
