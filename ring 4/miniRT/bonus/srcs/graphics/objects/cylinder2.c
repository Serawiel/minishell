/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:17:29 by cprot             #+#    #+#             */
/*   Updated: 2025/11/19 16:39:10 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static int	check_cap_in_radius(t_vec3 point, t_cylinder *cyl, t_vec3 cap_c)
{
	t_vec3	to_center;
	double	dist;

	to_center = vec_sub(point, cap_c);
	dist = vec_length(to_center);
	if (dist > cyl->diameter / 2.0)
		return (0);
	return (1);
}

static int	calc_cap_t(t_ray ray, t_cylinder *cyl, t_vec3 cap_c, double *t)
{
	t_vec3	oc;
	double	denom;
	double	numer;
	t_vec3	point;

	denom = vec_dot(ray.direction, cyl->axis);
	if (fabs(denom) < 0.0001)
		return (0);
	oc = vec_sub(cap_c, ray.origin);
	numer = vec_dot(oc, cyl->axis);
	*t = numer / denom;
	if (*t < 0.001)
		return (0);
	point = vec_add(ray.origin, vec_scale(ray.direction, *t));
	return (check_cap_in_radius(point, cyl, cap_c));
}

int	intersect_cylinder_cap(t_ray ray, t_cylinder *cyl, double *t, int is_top)
{
	t_vec3	cap_center;
	double	offset;

	if (is_top)
		offset = cyl->height / 2.0;
	else
		offset = -cyl->height / 2.0;
	cap_center = vec_add(cyl->center, vec_scale(cyl->axis, offset));
	return (calc_cap_t(ray, cyl, cap_center, t));
}
