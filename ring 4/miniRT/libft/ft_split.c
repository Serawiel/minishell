/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:22:29 by scavalli          #+#    #+#             */
/*   Updated: 2025/11/19 15:29:18 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_charset(char c, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (true);
		i++;
	}
	return (false);
}

static size_t	count_words(char const *s, const char *charset)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	if (!s || !charset)
		return (0);
	while (s[i])
	{
		while (s[i] && is_charset(s[i], charset))
			i++;
		if (s[i] && !is_charset(s[i], charset))
		{
			words++;
			while (s[i] && !is_charset(s[i], charset))
				i++;
		}
	}
	return (words);
}

static void	fill_tab(char *new, char const *s, const char *charset)
{
	size_t	i;

	i = 0;
	while (s[i] && !is_charset(s[i], charset))
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
}

static void	set_mem(char **tab, char const *s, const char *charset)
{
	size_t	count;
	size_t	index;
	size_t	i;

	index = 0;
	i = 0;
	while (s[index])
	{
		count = 0;
		while (s[index + count] && !is_charset(s[index + count], charset))
			count++;
		if (count > 0)
		{
			tab[i] = malloc(sizeof(char) * (count + 1));
			if (!tab[i])
				return ;
			fill_tab(tab[i], (s + index), charset);
			i++;
			index = index + count;
		}
		else
			index++;
	}
	tab[i] = 0;
}

char	**ft_split(const char *s, const char *charset)
{
	size_t	words;
	char	**tab;

	if (!s)
		return (NULL);
	words = count_words(s, charset);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	set_mem(tab, s, charset);
	return (tab);
}
