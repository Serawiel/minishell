/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:18:46 by cprot             #+#    #+#             */
/*   Updated: 2025/11/19 16:05:07 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	set_cylinder_body_normal(t_ray ray, t_cylinder *cylinder,
		t_hit_record *rec)
{
	t_vec3	center_to_point;
	t_vec3	outward_normal;

	center_to_point = vec_sub(rec->point, cylinder->center);
	outward_normal = vec_perp_to_axis(center_to_point, cylinder->axis);
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

static void	set_cylinder_cap_normal(t_ray ray, t_cylinder *cylinder,
		t_hit_record *rec, int is_top)
{
	t_vec3	normal;

	if (is_top)
		normal = cylinder->axis;
	else
		normal = vec_scale(cylinder->axis, -1.0);
	if (vec_dot(ray.direction, normal) > 0)
	{
		rec->front_face = 0;
		rec->normal = vec_scale(normal, -1.0);
	}
	else
	{
		rec->front_face = 1;
		rec->normal = normal;
	}
}

static int	try_cylinder_body(t_ray ray, t_cylinder *cylinder,
		t_hit_record *rec)
{
	double	t;

	if (!intersect_cylinder_body(ray, cylinder, &t))
		return (0);
	if (t < 0.001 || t >= rec->t)
		return (0);
	rec->t = t;
	rec->point = vec_add(ray.origin, vec_scale(ray.direction, t));
	rec->type = OBJ_CYLINDER;
	rec->object = cylinder;
	set_cylinder_body_normal(ray, cylinder, rec);
	return (1);
}

static int	try_cylinder_cap(t_ray ray, t_cylinder *cylinder,
		t_hit_record *rec, int is_top)
{
	double	t;

	if (!intersect_cylinder_cap(ray, cylinder, &t, is_top))
		return (0);
	if (t < 0.001 || t >= rec->t)
		return (0);
	rec->t = t;
	rec->point = vec_add(ray.origin, vec_scale(ray.direction, t));
	rec->type = OBJ_CYLINDER;
	rec->object = cylinder;
	set_cylinder_cap_normal(ray, cylinder, rec, is_top);
	return (1);
}

int	hit_cylinder(t_ray ray, t_cylinder *cylinder, t_hit_record *rec)
{
	int	hit_anything;

	hit_anything = 0;
	if (try_cylinder_body(ray, cylinder, rec))
		hit_anything = 1;
	if (try_cylinder_cap(ray, cylinder, rec, 1))
		hit_anything = 1;
	if (try_cylinder_cap(ray, cylinder, rec, 0))
		hit_anything = 1;
	return (hit_anything);
}
