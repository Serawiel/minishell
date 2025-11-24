/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:57:37 by cprot             #+#    #+#             */
/*   Updated: 2025/11/24 10:57:39 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	verify_ambient(const char **line)
{
	float	ratio;
	char	**split_rgb;
	bool	is_valid;

	if (!is_valid_float(line[1]))
		return (false);
	ratio = ft_atof(line[1]);
	if (ratio < 0.0f || ratio > 1.0f)
		return (false);
	split_rgb = ft_split(line[2], ",");
	if (!split_rgb)
		return (false);
	is_valid = verify_rgb(split_rgb);
	free_tab(split_rgb);
	return (is_valid);
}
