/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:22:31 by cprot             #+#    #+#             */
/*   Updated: 2025/05/26 17:33:47 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start)
{
	char			*str;
	size_t			i;
	unsigned int	len;

	len = 0;
	while (s[start + len])
		len++;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
