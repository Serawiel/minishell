/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:10:00 by cprot             #+#    #+#             */
/*   Updated: 2025/11/19 16:39:15 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static double	calculate_discriminant_opt(t_vec3 oc, t_ray ray, double radius)
{
	double	a;
	double	h;
	double	c;

	a = vec_dot(ray.direction, ray.direction);
	h = vec_dot(ray.direction, oc);
	c = vec_dot(oc, oc) - radius * radius;
	return (h * h - a * c);
}

static double	solve_quadratic_opt(t_vec3 oc, t_ray ray, double discriminant)
{
	double	a;
	double	h;
	double	t;

	a = vec_dot(ray.direction, ray.direction);
	h = vec_dot(ray.direction, oc);
	t = (h - sqrt(discriminant)) / a;
	if (t < 0)
		t = (h + sqrt(discriminant)) / a;
	return (t);
}

int	intersect_sphere(t_ray ray, t_sphere *sphere, double *t)
{
	t_vec3	oc;
	double	radius;
	double	discriminant;

	oc = vec_sub(sphere->center, ray.origin);
	radius = sphere->diameter / 2.0;
	discriminant = calculate_discriminant_opt(oc, ray, radius);
	if (discriminant < 0)
		return (0);
	*t = solve_quadratic_opt(oc, ray, discriminant);
	if (*t < 0)
		return (0);
	return (1);
}
