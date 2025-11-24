/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:14:52 by cprot             #+#    #+#             */
/*   Updated: 2025/11/19 15:40:58 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	test_spheres(t_ray ray, t_object *obj, t_hit_record *rec)
{
	t_sphere	*sphere;
	int			hit_anything;

	hit_anything = 0;
	sphere = obj->spheres;
	while (sphere)
	{
		if (hit_sphere(ray, sphere, rec))
			hit_anything = 1;
		sphere = sphere->next;
	}
	return (hit_anything);
}

static int	test_planes(t_ray ray, t_object *obj, t_hit_record *rec)
{
	t_plane	*plane;
	int		hit_anything;

	hit_anything = 0;
	plane = obj->planes;
	while (plane)
	{
		if (hit_plane(ray, plane, rec))
			hit_anything = 1;
		plane = plane->next;
	}
	return (hit_anything);
}

static int	test_cylinders(t_ray ray, t_object *obj, t_hit_record *rec)
{
	t_cylinder	*cylinder;
	int			hit_anything;

	hit_anything = 0;
	cylinder = obj->cylinders;
	while (cylinder)
	{
		if (hit_cylinder(ray, cylinder, rec))
			hit_anything = 1;
		cylinder = cylinder->next;
	}
	return (hit_anything);
}

int	hit_world(t_ray ray, t_object *obj, t_hit_record *rec)
{
	int	hit_anything;

	hit_anything = 0;
	if (test_spheres(ray, obj, rec))
		hit_anything = 1;
	if (test_planes(ray, obj, rec))
		hit_anything = 1;
	if (test_cylinders(ray, obj, rec))
		hit_anything = 1;
	return (hit_anything);
}
