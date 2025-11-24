/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:12:01 by cprot             #+#    #+#             */
/*   Updated: 2025/11/18 11:06:24 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_environment(t_environment *env)
{
	if (!env)
		return ;
	if (env->ambient)
		free(env->ambient);
	if (env->camera)
		free(env->camera);
	if (env->light)
		free(env->light);
	free(env);
}

static void	free_spheres(t_sphere *lst)
{
	t_sphere	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

static void	free_planes(t_plane *lst)
{
	t_plane	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

static void	free_cylinders(t_cylinder *lst)
{
	t_cylinder	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

void	free_objects(t_object *obj)
{
	if (!obj)
		return ;
	if (obj->spheres)
		free_spheres(obj->spheres);
	if (obj->planes)
		free_planes(obj->planes);
	if (obj->cylinders)
		free_cylinders(obj->cylinders);
	free(obj);
}
