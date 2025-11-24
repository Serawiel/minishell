/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coraline <coraline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:09:46 by cprot             #+#    #+#             */
/*   Updated: 2025/11/21 18:38:14 by coraline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	intersect_plane(t_ray ray, t_plane *plane, double *t)
{
	double	denom;
	double	numer;
	t_vec3	oc;

	denom = vec_dot(ray.direction, plane->normal);
	if (fabs(denom) < 0.0001)
		return (0);
	oc = vec_sub(plane->point, ray.origin);
	numer = vec_dot(oc, plane->normal);
	*t = numer / denom;
	if (*t < 0)
		return (0);
	return (1);
}
