/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:17:55 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:15:51 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		number;
	char	*res;

	if (!ft_valid_base(base_from) || !ft_valid_base(base_to))
		return (NULL);
	number = ft_atoi_base(nbr, base_from);
	res = ft_itoa_base(number, base_to);
	if (!res)
		return (NULL);
	return (res);
}

/*
#include <stdio.h>
int	main(void)
{
	char	start[] = "1111";
	char	*end;
	char	base_from[] = "01";
	char	base_to[] = "0123456789abcdef";
	end = ft_convert_base(start, base_from, base_to);
	if (!end)
		return (0);
	printf("%s\tin base: %s\nconverts to\n%s\tin base: %s\n",
			start, base_from, end, base_to);
	free(end);
	return (0);
}
*/
