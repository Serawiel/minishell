/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_hex_printf.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:03:47 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/22 14:29:51 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptr_printf(va_list args, int *len)
{
	void	*ptr;

	ptr = va_arg(args, void *);
	if (ptr != NULL)
		ft_putstr_printf("0x", len);
	ft_putptr_hex_printf((unsigned long)ptr, len);
}

void	ft_putptr_hex_printf(unsigned long n, int *len)
{
	if (n == 0)
	{
		ft_putstr_printf("(nil)", len);
		return ;
	}
	if (n >= 16)
		ft_putptr_hex_printf(n / 16, len);
	write(1, &"0123456789abcdef"[n % 16], 1);
	(*len)++;
}
