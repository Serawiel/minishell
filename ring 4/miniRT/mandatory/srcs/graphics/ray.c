/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coraline <coraline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:11:12 by cprot             #+#    #+#             */
/*   Updated: 2025/11/21 18:43:11 by coraline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	create_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = vec_normalize(direction);
	return (ray);
}

void	setup_camera(t_minirt *rt, t_camera_basis *cam)
{
	t_vec3	world_up;
	double	aspect_ratio;
	double	fov_rad;

	cam->forward = vec_normalize(rt->env->camera->orientation);
	if (fabs(cam->forward.y) > 0.999)
		world_up = (t_vec3){0.0, 0.0, 1.0};
	else
		world_up = (t_vec3){0.0, 1.0, 0.0};
	cam->right = vec_normalize(vec_cross(world_up, cam->forward));
	cam->up = vec_cross(cam->forward, cam->right);
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	fov_rad = rt->env->camera->fov * M_PI / 180.0;
	cam->viewport_height = 2.0 * tan(fov_rad / 2.0);
	cam->viewport_width = cam->viewport_height * aspect_ratio;
}

double	random_double(int x, int y, int sample)
{
	double	value;
	int		seed;

	seed = x * 10000 + y * 10 + sample;
	value = sin(seed * 12.9898) * 43758.5453;
	return (value - floor(value));
}

t_ray	generate_ray(t_minirt *rt, t_camera_basis *cam, int x, int y)
{
	double	u;
	double	v;
	t_vec3	viewport_point;
	t_vec3	direction;
	double	offset[2];

	offset[0] = random_double(x, y, rt->sample_index * 2) - 0.5;
	offset[1] = random_double(x, y, rt->sample_index * 2 + 1) - 0.5;
	u = (((double)x + 0.5 + offset[0]) / (double)WIDTH - 0.5);
	v = (0.5 - ((double)y + 0.5 + offset[1]) / (double)HEIGHT);
	viewport_point = rt->env->camera->position;
	viewport_point = vec_add(viewport_point, cam->forward);
	viewport_point = vec_add(viewport_point, vec_scale(cam->right, u
				* cam->viewport_width));
	viewport_point = vec_add(viewport_point, vec_scale(cam->up, v
				* cam->viewport_height));
	direction = vec_sub(viewport_point, rt->env->camera->position);
	return (create_ray(rt->env->camera->position, direction));
}
