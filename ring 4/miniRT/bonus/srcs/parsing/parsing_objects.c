/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coraline <coraline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:54:27 by scavalli          #+#    #+#             */
/*   Updated: 2025/11/21 18:40:29 by coraline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	parse_sphere(char **line, t_environment **env, t_object **obj)
{
	t_sphere	*new_sphere;
	t_sphere	*temp;

	new_sphere = malloc(sizeof(t_sphere));
	new_sphere->center = parse_vector(line[1], env);
	new_sphere->diameter = parse_double(line[2], 0.0, DBL_MAX, env);
	new_sphere->color = parse_color(line[3], env);
	new_sphere->next = NULL;
	if (!(*obj)->spheres)
		(*obj)->spheres = new_sphere;
	else
	{
		temp = (*obj)->spheres;
		while (temp->next)
			temp = temp->next;
		temp->next = new_sphere;
	}
}

void	parse_plane(char **line, t_environment **env, t_object **obj)
{
	t_plane	*new_plane;
	t_plane	*temp;

	new_plane = malloc(sizeof(t_plane));
	new_plane->point = parse_vector(line[1], env);
	new_plane->normal = parse_vector_range(line[2], -1.0, 1.0, env);
	new_plane->color = parse_color(line[3], env);
	new_plane->next = NULL;
	if (!(*obj)->planes)
		(*obj)->planes = new_plane;
	else
	{
		temp = (*obj)->planes;
		while (temp->next)
			temp = temp->next;
		temp->next = new_plane;
	}
}

void	parse_cylinder(char **line, t_environment **env, t_object **obj)
{
	t_cylinder	*new_cylinder;
	t_cylinder	*temp;

	new_cylinder = malloc(sizeof(t_cylinder));
	new_cylinder->center = parse_vector(line[1], env);
	new_cylinder->axis = parse_vector_range(line[2], -1.0, 1.0, env);
	new_cylinder->diameter = parse_double(line[3], 0.0, DBL_MAX, env);
	new_cylinder->height = parse_double(line[4], 0.0, DBL_MAX, env);
	new_cylinder->color = parse_color(line[5], env);
	new_cylinder->next = NULL;
	if (!(*obj)->cylinders)
		(*obj)->cylinders = new_cylinder;
	else
	{
		temp = (*obj)->cylinders;
		while (temp->next)
			temp = temp->next;
		temp->next = new_cylinder;
	}
}
