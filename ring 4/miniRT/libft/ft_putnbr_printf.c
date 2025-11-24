/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:29:18 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/22 14:30:49 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_printf(int n, int *len)
{
	char	c;

	if (n == -2147483648)
	{
		ft_putstr_printf("-2147483648", len);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_printf('-', len);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_printf(n / 10, len);
	}
	c = (n % 10) + '0';
	ft_putchar_printf(c, len);
}

void	ft_put_unsigned_nbr_printf(unsigned int n, int *len)
{
	char	c;

	if (n >= 10)
	{
		ft_putnbr_printf(n / 10, len);
	}
	c = (n % 10) + '0';
	ft_putchar_printf(c, len);
}
