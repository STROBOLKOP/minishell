/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:22:05 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:16:05 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

int	ft_c_fmt(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

// const char, change in libft pls
int	ft_s_fmt(char *s)
{
	if (!s)
		return (ft_s_fmt("(null)"));
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}

int	ft_i_fmt(int n, t_field *field)
{
	char	*n_str;
	size_t	len;

	n_str = ft_itoa(n);
	if (n_str)
	{
		len = 0;
		if (field->prefix && n >= 0)
			len = ft_c_fmt(field->prefix);
		ft_putstr_fd(n_str, 1);
		len += ft_strlen(n_str);
		free(n_str);
		return (len);
	}
	return (-1);
}

int	ft_u_fmt(unsigned int n)
{
	char	*n_str;
	size_t	len;

	n_str = ft_utoa(n);
	if (n_str)
	{
		ft_putstr_fd(n_str, 1);
		len = ft_strlen(n_str);
		free(n_str);
		return (len);
	}
	return (-1);
}

int	ft_x_fmt(int n, char uppercase, t_field *field)
{
	char	*str;
	char	*base;
	size_t	len;

	if (uppercase)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	str = ft_utoa_base(n, base);
	if (str)
	{
		len = 0;
		if (field->alt && *str != '0')
		{
			if (uppercase)
				len = ft_s_fmt("0X");
			else
				len = ft_s_fmt("0x");
		}
		ft_putstr_fd(str, 1);
		len += ft_strlen(str);
		free(str);
		return (len);
	}
	return (-1);
}
