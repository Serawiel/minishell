/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:10:54 by cprot             #+#    #+#             */
/*   Updated: 2025/11/19 16:50:30 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	is_in_shadow(t_vec3 point, t_environment *env, t_object *obj)
{
	t_vec3			to_light;
	double			distance_to_light;
	t_ray			ray_to_light;
	t_hit_record	shadow_rec;

	to_light = vec_sub(env->light->position, point);
	distance_to_light = vec_length(to_light);
	ray_to_light.direction = vec_normalize(to_light);
	ray_to_light.origin = vec_add(point, vec_scale(ray_to_light.direction,
				0.001));
	shadow_rec.t = distance_to_light;
	if (hit_world(ray_to_light, obj, &shadow_rec))
	{
		if (shadow_rec.t < distance_to_light - 0.001)
			return (1);
	}
	return (0);
}

t_vec3	calculate_lighting(t_hit_record *rec, t_environment *env, t_object *obj)
{
	t_vec3	obj_color;
	t_vec3	ambient;
	t_vec3	light_dir;
	t_vec3	diffuse;
	double	diff;

	obj_color = get_object_color(rec);
	ambient = vec_mult(obj_color, color_to_vec3(env->ambient->color.r,
				env->ambient->color.g, env->ambient->color.b));
	ambient = vec_scale(ambient, env->ambient->ratio);
	if (is_in_shadow(rec->point, env, obj))
		return (ambient);
	light_dir = vec_sub(env->light->position, rec->point);
	light_dir = vec_normalize(light_dir);
	diff = vec_dot(rec->normal, light_dir);
	if (diff < 0.0)
		diff = 0.0;
	diffuse = vec_scale(obj_color, env->light->brightness * diff);
	return (vec_add(ambient, diffuse));
}
