/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:49:51 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/22 14:30:05 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_printf(char *str, int *len)
{
	size_t	i;

	i = 0;
	if (str == NULL)
	{
		ft_putstr_printf("(null)", len);
		return ;
	}
	while (str[i])
	{
		ft_putchar_printf(str[i], len);
		i++;
	}
}

void	ft_putchar_printf(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}
