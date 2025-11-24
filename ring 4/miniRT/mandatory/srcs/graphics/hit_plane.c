/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:40:11 by cprot             #+#    #+#             */
/*   Updated: 2025/11/19 15:40:37 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	set_plane_normal(t_ray ray, t_plane *plane, t_hit_record *rec)
{
	double	denom;

	denom = vec_dot(ray.direction, plane->normal);
	if (denom < 0)
	{
		rec->front_face = 1;
		rec->normal = plane->normal;
	}
	else
	{
		rec->front_face = 0;
		rec->normal = vec_scale(plane->normal, -1.0);
	}
}

int	hit_plane(t_ray ray, t_plane *plane, t_hit_record *rec)
{
	double	t;

	if (!intersect_plane(ray, plane, &t))
		return (0);
	if (t < 0.001 || t >= rec->t)
		return (0);
	rec->t = t;
	rec->point = vec_add(ray.origin, vec_scale(ray.direction, t));
	rec->type = OBJ_PLANE;
	rec->object = plane;
	set_plane_normal(ray, plane, rec);
	return (1);
}
