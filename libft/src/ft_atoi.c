/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:03:06 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:15:50 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

static int	ft_between_incl(int val, int min, int max)
{
	if (min <= val && val <= max)
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	number;

	sign = 1;
	number = 0;
	while (ft_between_incl(*nptr, '\t', '\r') || *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			sign *= -1;
	while (ft_between_incl(*nptr, '0', '9'))
		number = number * 10 + (*nptr++ - '0');
	return (number * sign);
}
