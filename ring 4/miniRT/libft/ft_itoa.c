/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:56:28 by scavalli          #+#    #+#             */
/*   Updated: 2025/03/14 12:08:02 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return (ptr);
}

static void	create_tab(int n, char *tab, int i)
{
	int	minus;

	minus = 0;
	tab[i] = '\0';
	i--;
	if (n == -2147483648)
	{
		ft_strcpy(tab, "-2147483648");
		return ;
	}
	if (n < 0)
	{
		n = -n;
		minus = 1;
	}
	while (i >= minus)
	{
		tab[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	if (minus == 1)
		tab[i] = '-';
	return ;
}

char	*ft_itoa(int n)
{
	char	*tab;
	int		copy;
	int		i;

	copy = n;
	i = 0;
	while (copy >= 1 || copy <= -1)
	{
		copy /= 10;
		i++;
	}
	if (n < 0 || n == 0)
		i++;
	tab = malloc(i + 1);
	if (!tab)
		return (NULL);
	create_tab(n, tab, i);
	return (tab);
}
