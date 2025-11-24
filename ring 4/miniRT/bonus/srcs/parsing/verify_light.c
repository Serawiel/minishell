/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:58:49 by cprot             #+#    #+#             */
/*   Updated: 2025/11/24 10:58:50 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static bool	verify_light_params(const char **line)
{
	char	**split_coord;
	char	**split_rgb;
	float	brightness;
	bool	is_valid;

	split_coord = ft_split(line[1], ",");
	if (!split_coord || !verify_coordinates(split_coord))
		return (free_tab(split_coord), false);
	free_tab(split_coord);
	if (!is_valid_float(line[2]))
		return (false);
	brightness = ft_atof(line[2]);
	if (brightness < 0.0f || brightness > 1.0f)
		return (false);
	split_rgb = ft_split(line[3], ",");
	if (!split_rgb)
		return (false);
	is_valid = verify_rgb(split_rgb);
	return (free_tab(split_rgb), is_valid);
}

bool	verify_light(const char **line)
{
	if (!line[0] || ft_strncmp(line[0], "L", 2) != 0)
		return (false);
	if (!line[1] || !line[2] || !line[3] || line[4])
		return (false);
	return (verify_light_params(line));
}
