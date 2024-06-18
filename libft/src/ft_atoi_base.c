/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:56:47 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:15:50 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

static int	ft_char_in_str(char *str, char c)
{
	while (*str)
		if (*str++ == c)
			return (1);
	return (0);
}

int	ft_atoi_base(char *str, char *base)
{
	int	sign;
	int	number;
	int	base_len;
	int	base_idx;

	sign = 1;
	if (!ft_valid_base(base))
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		sign -= 2 * (*str++ == '-');
	base_len = ft_strlen(base);
	number = 0;
	while (ft_char_in_str(base, *str))
	{
		base_idx = -1;
		while (++base_idx < base_len)
			if (base[base_idx] == *str)
				number = number * base_len + base_idx;
		str++;
	}
	return (number * sign);
}

/*
#include <stdio.h>
int	main(void)
{
	char	str[] = "1111";
	char	base[] = "0123456789abcdef";

	printf("%d\n", ft_atoi_base(str, base));
	return (0);
}
*/
