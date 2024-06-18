/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:59:55 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:16:24 by efret            ###   ########.fr       */
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

int	ft_valid_base(char *base)
{
	char	seen_char[128];
	int		idx;

	idx = 0;
	while (idx < 128)
		seen_char[idx++] = 0;
	idx = 0;
	if (!(*base && *(base + 1)))
		return (0);
	while (*base)
	{
		if (*base == '+' || *base == '-' || (*base <= ' ' || 127 <= *base))
			return (0);
		if (ft_char_in_str(seen_char, *base))
			return (0);
		seen_char[idx] = *base;
		idx++;
		base++;
	}
	return (1);
}
