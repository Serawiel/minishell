/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:58:53 by cprot             #+#    #+#             */
/*   Updated: 2025/11/24 10:58:54 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static bool	verify_normal(char **split_normal)
{
	float	val;
	int		i;

	if (!split_normal[0] || !split_normal[1] || !split_normal[2])
		return (false);
	if (split_normal[3])
		return (false);
	i = -1;
	while (++i < 3)
	{
		if (!is_valid_float(split_normal[i]))
			return (false);
		val = ft_atof(split_normal[i]);
		if (val < -1.0f || val > 1.0f)
			return (false);
	}
	return (true);
}

bool	verify_plane(const char **line)
{
	char	**split_coord;
	char	**split_normal;
	char	**split_rgb;
	bool	is_valid;

	split_coord = ft_split(line[1], ",");
	if (!split_coord || !verify_coordinates(split_coord))
		return (free_tab(split_coord), false);
	free_tab(split_coord);
	split_normal = ft_split(line[2], ",");
	if (!split_normal || !verify_normal(split_normal))
		return (free_tab(split_normal), false);
	free_tab(split_normal);
	split_rgb = ft_split(line[3], ",");
	if (!split_rgb)
		return (false);
	is_valid = verify_rgb(split_rgb);
	return (free_tab(split_rgb), is_valid);
}
