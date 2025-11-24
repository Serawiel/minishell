/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:58:39 by cprot             #+#    #+#             */
/*   Updated: 2025/11/24 10:58:40 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static bool	verify_orientation(char **split_orient)
{
	float	val;
	int		i;

	if (!split_orient[0] || !split_orient[1] || !split_orient[2])
		return (false);
	if (split_orient[3])
		return (false);
	i = -1;
	while (++i < 3)
	{
		if (!is_valid_float(split_orient[i]))
			return (false);
		val = ft_atof(split_orient[i]);
		if (val < -1.0f || val > 1.0f)
			return (false);
	}
	return (true);
}

bool	verify_camera_(const char **line)
{
	char	**split_coord;
	char	**split_orient;
	int		fov;

	split_coord = ft_split(line[1], ",");
	if (!split_coord || !verify_coordinates(split_coord))
		return (free_tab(split_coord), false);
	free_tab(split_coord);
	split_orient = ft_split(line[2], ",");
	if (!split_orient || !verify_orientation(split_orient))
		return (free_tab(split_orient), false);
	free_tab(split_orient);
	if (!is_valid_number(line[3]))
		return (false);
	fov = ft_atoi(line[3]);
	if (fov < 0 || fov > 180)
		return (false);
	return (true);
}
