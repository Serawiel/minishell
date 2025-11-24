/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coraline <coraline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:10:54 by cprot             #+#    #+#             */
/*   Updated: 2025/11/21 18:15:12 by coraline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static int	is_in_shadow(t_vec3 point, t_light *light, t_object *obj)
{
	t_vec3			to_light;
	double			distance_to_light;
	t_ray			ray_to_light;
	t_hit_record	shadow_rec;

	to_light = vec_sub(light->position, point);
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

static t_vec3	calc_specular(t_hit_record *rec, t_light *light,
		t_vec3 view_dir, t_vec3 light_dir)
{
	t_vec3	reflect_dir;
	t_vec3	light_color;
	double	spec;
	double	shininess;

	if (rec->type == OBJ_PLANE)
		return ((t_vec3){0, 0, 0});
	reflect_dir = vec_sub(vec_scale(rec->normal, 2.0 * vec_dot(rec->normal,
					light_dir)), light_dir);
	reflect_dir = vec_normalize(reflect_dir);
	spec = vec_dot(view_dir, reflect_dir);
	if (spec <= 0)
		spec = 0;
	if (rec->type == OBJ_CYLINDER)
		shininess = 150.0;
	else
		shininess = 32.0;
	spec = pow(spec, shininess);
	light_color = color_to_vec3(light->color.r, light->color.g, light->color.b);
	return (vec_scale(light_color, spec * light->brightness));
}

static t_vec3	calc_diffuse(t_vec3 obj_color, t_light *light, t_vec3 normal,
		t_vec3 light_dir)
{
	t_vec3	light_color;
	t_vec3	diffuse;
	double	diff;

	light_color = color_to_vec3(light->color.r, light->color.g, light->color.b);
	diff = vec_dot(normal, light_dir);
	if (diff < 0.0)
		diff = 0.0;
	diffuse = vec_mult(obj_color, light_color);
	diffuse = vec_scale(diffuse, light->brightness * diff);
	return (diffuse);
}

static t_vec3	calc_one_light(t_hit_record *rec, t_light *light,
		t_vec3 view_dir, t_object *obj)
{
	t_vec3	obj_color;
	t_vec3	light_dir;
	t_vec3	diffuse;
	t_vec3	specular;

	if (is_in_shadow(rec->point, light, obj))
		return ((t_vec3){0, 0, 0});
	obj_color = get_object_color(rec);
	light_dir = vec_sub(light->position, rec->point);
	light_dir = vec_normalize(light_dir);
	diffuse = calc_diffuse(obj_color, light, rec->normal, light_dir);
	specular = calc_specular(rec, light, view_dir, light_dir);
	return (vec_add(diffuse, specular));
}

t_vec3	calculate_lighting(t_hit_record *rec, t_environment *env, t_object *obj)
{
	t_vec3	obj_color;
	t_vec3	ambient;
	t_vec3	view_dir;
	t_vec3	result;
	t_light	*current;

	obj_color = get_object_color(rec);
	ambient = vec_mult(obj_color, color_to_vec3(env->ambient->color.r,
				env->ambient->color.g, env->ambient->color.b));
	ambient = vec_scale(ambient, env->ambient->ratio);
	result = ambient;
	view_dir = vec_sub(env->camera->position, rec->point);
	view_dir = vec_normalize(view_dir);
	current = env->light;
	while (current)
	{
		result = vec_add(result, calc_one_light(rec, current, view_dir, obj));
		current = current->next;
	}
	return (result);
}
