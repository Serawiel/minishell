/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:58:45 by cprot             #+#    #+#             */
/*   Updated: 2025/11/24 10:58:46 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static bool	verify_axis(char **split_axis)
{
	float	val;
	int		i;

	if (!split_axis[0] || !split_axis[1] || !split_axis[2])
		return (false);
	if (split_axis[3])
		return (false);
	i = -1;
	while (++i < 3)
	{
		if (!is_valid_float(split_axis[i]))
			return (false);
		val = ft_atof(split_axis[i]);
		if (val < -1.0f || val > 1.0f)
			return (false);
	}
	return (true);
}

bool	verify_cylinder(const char **line)
{
	char	**split_coord;
	char	**split_axis;
	char	**split_rgb;
	bool	is_valid;

	split_coord = ft_split(line[1], ",");
	if (!split_coord || !verify_coordinates(split_coord))
		return (free_tab(split_coord), false);
	free_tab(split_coord);
	split_axis = ft_split(line[2], ",");
	if (!split_axis || !verify_axis(split_axis))
		return (free_tab(split_axis), false);
	free_tab(split_axis);
	if (!is_valid_float(line[3]) || !is_valid_float(line[4]))
		return (false);
	split_rgb = ft_split(line[5], ",");
	if (!split_rgb)
		return (false);
	is_valid = verify_rgb(split_rgb);
	return (free_tab(split_rgb), is_valid);
}
