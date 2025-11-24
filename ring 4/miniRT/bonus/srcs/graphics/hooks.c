/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:10:23 by cprot             #+#    #+#             */
/*   Updated: 2025/11/19 16:39:38 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	close_window(t_minirt *rt)
{
	mlx_destroy_image(rt->mlx, rt->img);
	mlx_destroy_window(rt->mlx, rt->win);
	mlx_destroy_display(rt->mlx);
	free(rt->mlx);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_minirt *rt)
{
	if (keycode == 65307)
		close_window(rt);
	return (0);
}

int	expose_hook(t_minirt *rt)
{
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img, 0, 0);
	return (0);
}

void	apply_hooks(t_minirt *rt)
{
	mlx_key_hook(rt->win, key_press, rt);
	mlx_hook(rt->win, 17, 0, close_window, rt);
	mlx_expose_hook(rt->win, expose_hook, rt);
}
