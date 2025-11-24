/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:20:49 by cprot             #+#    #+#             */
/*   Updated: 2025/05/26 16:52:46 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr(char *a, char *b)
{
	int	i;
	int	j;

	if (!b || !b[0])
		return (1);
	if (!a)
		return (0);
	i = 0;
	while (a[i])
	{
		j = 0;
		while (a[i + j] && b[j] && a[i + j] == b[j])
			j++;
		if (!b[j])
			return (1);
		i++;
	}
	return (0);
}
