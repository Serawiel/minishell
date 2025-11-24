/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:58:59 by cprot             #+#    #+#             */
/*   Updated: 2025/11/24 10:59:00 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

bool	verify_sphere(const char **line)
{
	char	**split_coord;
	char	**split_rgb;
	bool	is_valid;

	split_coord = ft_split(line[1], ",");
	if (!split_coord || !verify_coordinates(split_coord))
		return (free_tab(split_coord), false);
	free_tab(split_coord);
	if (!is_valid_float(line[2]))
		return (false);
	split_rgb = ft_split(line[3], ",");
	if (!split_rgb)
		return (false);
	is_valid = verify_rgb(split_rgb);
	return (free_tab(split_rgb), is_valid);
}
