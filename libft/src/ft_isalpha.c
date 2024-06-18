/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:37:09 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:15:52 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

int	ft_isalpha(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
		return (1);
	return (0);
}

/*
#include "libft.h"
#include <stdio.h>
#include <string.h>

// A bit of small tests, !!! not checking edge cases here.
int	main(void)
{
	char	**s = ft_split("1234 -561 2147483647 -2147483648", ' ');
	if (!s)
	{
		printf("Malloc failed");
		return (0);
	}

	//Test atoi on split
	for	(int i = 0; s[i]; i++)
	{
		printf("\natoi: %15d\nft_atoi: %12d\n", atoi(s[i]), ft_atoi(s[i]));
	}

	//Test strlen, bzero
	size_t	first_len = ft_strlen(s[0]);
	ft_bzero(s[0], first_len);
	if (s[0][0] == 0 && s[0][first_len] == 0)
		printf("\nFirst split string set to NULL\n");
	else
		printf("\nFAIL ft_bzero: %s\n", s[0]);

	// Test memcpy, memcmp, putnbr_fd and putendl_fd
	ft_memcpy(s[0], s[1], first_len);

	if (!ft_memcmp(s[0], s[1], first_len))
	{
		printf("\nFirst string is now equal to second: \n");
		ft_putendl_fd(s[1], 1);
		ft_putnbr_fd(ft_atoi(s[0]), 1);
		printf("\n");
	}
	else
	{
		printf("\nFAIL ft_memcpy\n");
	}

	char	*joined = ft_strjoin(s[2], s[3]);
	if (joined)
	{
		ft_putendl_fd(joined, 1);
		free(joined);
	}

	for (int i = 0; s[i]; i++)
		free(s[i]);
	free(s);

	return (0);
}
*/
