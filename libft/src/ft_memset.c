/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:30:54 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:16:03 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	data;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	data = (unsigned char)c;
	while (i < n)
		ptr[i++] = data;
	return (s);
}
