/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:52:43 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/22 14:28:15 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	type_format(char specifier, va_list args, int *len)
{
	if (specifier == 'd' || specifier == 'i')
		ft_putnbr_printf(va_arg(args, int), len);
	else if (specifier == 'u')
		ft_put_unsigned_nbr_printf(va_arg(args, unsigned int), len);
	else if (specifier == 's')
		ft_putstr_printf(va_arg(args, char *), len);
	else if (specifier == '%')
		ft_putchar_printf('%', len);
	else if (specifier == 'c')
		ft_putchar_printf(va_arg(args, int), len);
	else if (specifier == 'p')
		ft_putptr_printf(args, len);
	else if (specifier == 'x')
		ft_putnbr_lowercase_hex_printf(va_arg(args, unsigned int), len);
	else if (specifier == 'X')
		ft_putnbr_uppercase_hex_printf(va_arg(args, unsigned int), len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	i;
	int		len;

	va_start(args, format);
	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			type_format(format[i + 1], args, &len);
			i += 2;
		}
		else
		{
			ft_putchar_printf(format[i], &len);
			i++;
		}
	}
	va_end(args);
	return (len);
}
