/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:18:04 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:16:01 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1ptr;
	unsigned char	*s2ptr;

	i = 0;
	s1ptr = (unsigned char *)s1;
	s2ptr = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while ((s1ptr[i] == s2ptr[i]) && i < n - 1)
		i++;
	return ((unsigned char)s1ptr[i] - (unsigned char)s2ptr[i]);
}
