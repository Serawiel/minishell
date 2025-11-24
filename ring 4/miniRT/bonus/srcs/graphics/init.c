/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:00:52 by cprot             #+#    #+#             */
/*   Updated: 2025/11/19 16:39:42 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	my_mlx_pixel_put(t_minirt *rt, int x, int y, int color)
{
	char	*dst;

	dst = rt->addr + (y * rt->line_length + x * (rt->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static t_vec3	render_single_pixel(t_minirt *rt, t_camera_basis *basis, int x,
		int y)
{
	t_ray	ray;
	t_vec3	pixel_color;
	t_vec3	accumulated_color;
	double	scale;

	accumulated_color = (t_vec3){0, 0, 0};
	scale = 1.0 / rt->env->camera->samples_per_pixel;
	rt->sample_index = 0;
	while (rt->sample_index < rt->env->camera->samples_per_pixel)
	{
		ray = generate_ray(rt, basis, x, y);
		pixel_color = ray_color(ray, rt->obj, rt->env);
		accumulated_color = vec_add(accumulated_color, pixel_color);
		rt->sample_index++;
	}
	return (vec_scale(accumulated_color, scale));
}

void	render_pixels(t_minirt *rt, t_camera_basis *basis)
{
	t_vec3	pixel_color;
	int		color;
	int		x;
	int		y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_color = render_single_pixel(rt, basis, x, y);
			color = vec3_to_int(pixel_color);
			my_mlx_pixel_put(rt, x, y, color);
			x++;
		}
		y++;
	}
}

void	init_minirt(t_environment *env, t_object *obj)
{
	t_minirt		rt;
	t_camera_basis	basis;

	rt.env = env;
	rt.obj = obj;
	rt.sample_index = 0;
	if (env->camera->samples_per_pixel == 0)
		env->camera->samples_per_pixel = QUALITY;
	rt.mlx = mlx_init();
	rt.win = mlx_new_window(rt.mlx, WIDTH, HEIGHT, "miniRT");
	rt.img = mlx_new_image(rt.mlx, WIDTH, HEIGHT);
	rt.addr = mlx_get_data_addr(rt.img, &rt.bits_per_pixel, &rt.line_length,
			&rt.endian);
	setup_camera(&rt, &basis);
	render_pixels(&rt, &basis);
	mlx_put_image_to_window(rt.mlx, rt.win, rt.img, 0, 0);
	apply_hooks(&rt);
	mlx_loop(rt.mlx);
}
