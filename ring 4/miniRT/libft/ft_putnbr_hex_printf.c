/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_printf.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:38:51 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/22 14:29:29 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_lowercase_hex_printf(unsigned int n, int *len)
{
	if (n >= 16)
		ft_putnbr_lowercase_hex_printf(n / 16, len);
	write(1, &"0123456789abcdef"[n % 16], 1);
	(*len)++;
}

void	ft_putnbr_uppercase_hex_printf(unsigned int n, int *len)
{
	if (n >= 16)
		ft_putnbr_uppercase_hex_printf(n / 16, len);
	write(1, &"0123456789ABCDEF"[n % 16], 1);
	(*len)++;
}
