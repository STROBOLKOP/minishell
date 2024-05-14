/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:48:51 by efret             #+#    #+#             */
/*   Updated: 2023/12/21 13:13:31 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	nbytes;
	void	*res;

	nbytes = nmemb * size;
	if (nmemb == 0 || size == 0 || nmemb > ((size_t) - 1) / size)
		return (NULL);
	res = malloc(nbytes);
	if (!res)
		return (NULL);
	ft_bzero(res, nbytes);
	return (res);
}
