/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:38:59 by cprot             #+#    #+#             */
/*   Updated: 2025/11/19 16:39:32 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static void	set_sphere_normal(t_ray ray, t_sphere *sphere, t_hit_record *rec)
{
	t_vec3	outward_normal;

	outward_normal = vec_sub(rec->point, sphere->center);
	outward_normal = vec_normalize(outward_normal);
	if (vec_dot(ray.direction, outward_normal) > 0)
	{
		rec->front_face = 0;
		rec->normal = vec_scale(outward_normal, -1.0);
	}
	else
	{
		rec->front_face = 1;
		rec->normal = outward_normal;
	}
}

int	hit_sphere(t_ray ray, t_sphere *sphere, t_hit_record *rec)
{
	double	t;

	if (!intersect_sphere(ray, sphere, &t))
		return (0);
	if (t < 0.001 || t >= rec->t)
		return (0);
	rec->t = t;
	rec->point = vec_add(ray.origin, vec_scale(ray.direction, t));
	rec->type = OBJ_SPHERE;
	rec->object = sphere;
	set_sphere_normal(ray, sphere, rec);
	return (1);
}
