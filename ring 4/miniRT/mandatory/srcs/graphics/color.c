/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:10:09 by cprot             #+#    #+#             */
/*   Updated: 2025/11/18 11:12:57 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	vec3_to_int(t_vec3 v)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255.999 * v.x);
	g = (int)(255.999 * v.y);
	b = (int)(255.999 * v.z);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return ((r << 16) | (g << 8) | b);
}

t_vec3	color_to_vec3(int r, int g, int b)
{
	t_vec3	new;

	new.x = r / 255.0;
	new.y = g / 255.0;
	new.z = b / 255.0;
	return (new);
}

t_vec3	get_object_color(t_hit_record *rec)
{
	t_color	color;

	if (rec->type == OBJ_SPHERE)
		color = ((t_sphere *)rec->object)->color;
	else if (rec->type == OBJ_PLANE)
		color = ((t_plane *)rec->object)->color;
	else if (rec->type == OBJ_CYLINDER)
		color = ((t_cylinder *)rec->object)->color;
	else
		return ((t_vec3){0, 0, 0});
	return (color_to_vec3(color.r, color.g, color.b));
}

t_vec3	ray_color(t_ray ray, t_object *obj, t_environment *env)
{
	t_hit_record	rec;

	rec.t = DBL_MAX;
	if (hit_world(ray, obj, &rec))
		return (calculate_lighting(&rec, env, obj));
	return ((t_vec3){0, 0, 0});
}
