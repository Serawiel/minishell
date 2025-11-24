/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ambient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:53:52 by scavalli          #+#    #+#             */
/*   Updated: 2025/11/19 15:31:42 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_ambient(char **line, t_environment **env)
{
	(*env)->ambient = malloc(sizeof(t_ambient));
	(*env)->ambient->ratio = parse_double(line[1], 0.0, 1.0, env);
	(*env)->ambient->color = parse_color(line[2], env);
}

void	parse_camera(char **line, t_environment **env, t_object **obj)
{
	(*env)->camera = malloc(sizeof(t_camera));
	(*env)->camera->position = parse_vector(line[1], env);
	(*env)->camera->orientation = parse_vector_range(line[2], -1.0, 1.0, env);
	(*env)->camera->fov = atoi(line[3]);
	if ((*env)->camera->fov < 0 || (*env)->camera->fov > 180)
		exit_with_error("Error: FOV out of range\n", env, obj);
}

void	parse_light(char **line, t_environment **env)
{
	(*env)->light = malloc(sizeof(t_light));
	(*env)->light->position = parse_vector(line[1], env);
	(*env)->light->brightness = parse_double(line[2], 0.0, 1.0, env);
	(*env)->light->color = parse_color(line[3], env);
}
