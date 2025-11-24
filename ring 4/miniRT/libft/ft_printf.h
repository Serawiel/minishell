/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:48:20 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/22 14:26:19 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_putstr_printf(char *str, int *len);
void	ft_putchar_printf(char c, int *len);
void	ft_put_unsigned_nbr_printf(unsigned int n, int *len);
void	ft_putnbr_lowercase_hex_printf(unsigned int n, int *len);
void	ft_putnbr_uppercase_hex_printf(unsigned int n, int *len);
void	ft_putptr_printf(va_list args, int *len);
void	ft_putptr_hex_printf(unsigned long n, int *len);
void	ft_putnbr_printf(int n, int *len);
int		ft_printf(const char *format, ...);

#endif