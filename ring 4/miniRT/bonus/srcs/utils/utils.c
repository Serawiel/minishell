/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coraline <coraline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:12:09 by cprot             #+#    #+#             */
/*   Updated: 2025/11/21 18:39:09 by coraline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

bool	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	is_valid_float(const char *str)
{
	int	i;
	int	has_dot;

	i = 0;
	has_dot = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (str[i] == '.' && !has_dot)
			has_dot = 1;
		else if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	verify_rgb(char **split_rgb)
{
	int	rgb[3];
	int	i;

	if (!split_rgb[0] || !split_rgb[1] || !split_rgb[2] || split_rgb[3])
		return (false);
	i = -1;
	while (++i < 3)
	{
		if (!is_valid_number(split_rgb[i]))
			return (false);
		rgb[i] = ft_atoi(split_rgb[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (false);
	}
	return (true);
}

bool	verify_coordinates(char **split_coord)
{
	int	i;

	if (!split_coord[0] || !split_coord[1] || !split_coord[2])
		return (false);
	if (split_coord[3])
		return (false);
	i = -1;
	while (++i < 3)
	{
		if (!is_valid_float(split_coord[i]))
			return (false);
	}
	return (true);
}
