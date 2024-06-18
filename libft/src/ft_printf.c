/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efret <efret@student.19.be>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:58:56 by efret             #+#    #+#             */
/*   Updated: 2024/06/18 14:16:05 by efret            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

int	ft_p_fmt(void *addr)
{
	char	*str;
	char	*base;
	size_t	len;

	if (!addr)
		return (ft_s_fmt("(nil)"));
	base = "0123456789abcdef";
	str = ft_ptoa_base((uintptr_t)addr, base);
	if (!str)
		return (-1);
	len = ft_s_fmt("0x");
	ft_putstr_fd(str, 1);
	len += ft_strlen(str);
	free(str);
	return (len);
}

t_field	*ft_fill_field_struct(const char **s)
{
	t_field	*field;

	field = ft_calloc(1, sizeof(t_field));
	if (!field)
		return (NULL);
	while (**s == '#' || **s == ' ' || **s == '+')
	{
		if (**s == '#')
			field->alt = 1;
		if (**s == ' ' && field->prefix < ' ')
			field->prefix = ' ';
		if (**s == '+' && field->prefix < '+')
			field->prefix = '+';
		(*s)++;
	}
	return (field);
}

int	ft_format_print(const char **s, va_list *ap)
{
	size_t	written;
	t_field	*field;

	(*s)++;
	field = ft_fill_field_struct(s);
	written = 0;
	if (**s == 'c')
		written += ft_c_fmt((char) va_arg(*ap, int));
	else if (**s == 's')
		written += ft_s_fmt(va_arg(*ap, char *));
	else if (**s == 'd' || **s == 'i')
		written += ft_i_fmt(va_arg(*ap, int), field);
	else if (**s == 'u')
		written += ft_u_fmt(va_arg(*ap, unsigned int));
	else if (**s == 'x' || **s == 'X')
		written += ft_x_fmt(va_arg(*ap, int), **s - 'x', field);
	else if (**s == 'p')
		written += ft_p_fmt(va_arg(*ap, void *));
	else if (**s == '%')
		written += ft_c_fmt('%');
	else
		return (-1);
	free(field);
	return (written);
}

int	ft_printf(const char *s, ...)
{
	int		len;
	va_list	ap;

	va_start(ap, s);
	len = 0;
	while (*s)
	{
		if (*s == '%')
		{
			len += ft_format_print(&s, &ap);
		}
		else
		{
			ft_putchar_fd(*s, 1);
			len++;
		}
		s++;
	}
	va_end(ap);
	return (len);
}

/*
#include "bonus/incl_bonus/ft_printf_bonus.h"
#include <limits.h>
#include <stdio.h>
int main()
{
	int	tot_printed;
	char *str;
	char *str2;
	char *str3;

	str = "hey hey";
	str2 = "HOY";
	str3 = "KMP";
 
	tot_printed = ft_printf("%c\n%s\n%i\n% i\n% i\n%i\
	\n% u\n%+u\n%+# x\n%#X\n%p\n%p\n%p\n",
			'z',
			(char *)NULL,
			-2147483647, -2147483647,
			2147483647, 2147483647,
			256, 928,
			-123, 3210,
			&tot_printed, &str, (void *)NULL);
	ft_printf("\nreturn: %d\n\n", tot_printed);
	tot_printed = printf("%c\n%s\n%i\n% i\n% i\
	\n%i\n% u\n%+u\n%+# x\n%#X\n%p\n%p\n%p\n",
			'z',
			(char *)NULL,
			-2147483647, -2147483647,
			2147483647, 2147483647,
			256, 928,
			-123, 3210,
			&tot_printed, &str, (void *)NULL);
	printf("\nreturn: %d\n\n", tot_printed);
	
	tot_printed = ft_printf(" %p %p ", LONG_MIN, LONG_MAX);
	ft_printf("\nreturn: %d\n\n", tot_printed);
	tot_printed = printf(" %p %p ", LONG_MIN, LONG_MAX);
	printf("\nreturn: %d\n\n", tot_printed);
	
	tot_printed = ft_printf(" %p %p ", ULONG_MAX, -ULONG_MAX);
	ft_printf("\nreturn: %d\n\n", tot_printed);
	tot_printed = printf(" %p %p ", ULONG_MAX, -ULONG_MAX);
	printf("\nreturn: %d\n\n", tot_printed);


	ft_printf("FT_PRINTF:\n");
	ft_printf(" %#x\n", 0);
	ft_printf(" %#x\n", LONG_MIN);
	ft_printf(" %#x %#x %#x %#x %#x %#x %#x\n",
			INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	ft_printf(" %#X\n", 0);
	ft_printf(" %#X\n", LONG_MIN);
	ft_printf(" %#X %#X %#X %#X %#X %#X %#X\n",
			INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);

	ft_printf("PRINTF:\n");
	printf(" %#x\n", 0);
	printf(" %#x\n", LONG_MIN);
	printf(" %#x %#x %#x %#x %#x %#x %#x\n",
			INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	printf(" %#X\n", 0);
	printf(" %#X\n", LONG_MIN);
	printf(" %#X %#X %#X %#X %#X %#X %#X\n",
			INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);

	ft_printf("FT_PRINTF:\n");
	ft_printf(" % d\n", 0);
	ft_printf(" % d\n", LONG_MIN);
	ft_printf(" % d % d % d % d % d % d % d\n",
			INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	ft_printf(" % i\n", 0);
	ft_printf(" % i\n", LONG_MIN);
	ft_printf(" % i % i % i % i % i % i % i\n",
			INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);

	ft_printf("PRINTF:\n");
	printf(" % d\n", 0);
	printf(" % d\n", LONG_MIN);
	printf(" % d % d % d % d % d % d % d\n",
			INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	printf(" % i\n", 0);
	printf(" % i\n", LONG_MIN);
	printf(" % i % i % i % i % i % i % i\n",
			INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);

	ft_printf("FT_PRINTF:\n");
	ft_printf(" %+d\n", 0);
	ft_printf(" %+d\n", LONG_MIN);
	ft_printf(" %+d %+d %+d %+d %+d %+d %+d\n",
			INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	ft_printf(" %+i\n", 0);
	ft_printf(" %+i\n", LONG_MIN);

	ft_printf("PRINTF:\n");
	printf(" %+d\n", 0);
	printf(" %+d\n", LONG_MIN);
	printf(" %+d %+d %+d %+d %+d %+d %+d\n",
			INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	printf(" %+i\n", 0);
	printf(" %+i\n", LONG_MIN);
	return (0);
}
*/
