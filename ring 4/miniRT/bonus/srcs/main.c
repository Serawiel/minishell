/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:53:40 by cprot             #+#    #+#             */
/*   Updated: 2025/11/19 16:42:46 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	init_structs(t_environment **env, t_object **obj)
{
	*env = malloc(sizeof(t_environment));
	if (!*env)
		exit_with_error("Memory allocation failed", NULL, NULL);
	(*env)->ambient = NULL;
	(*env)->camera = NULL;
	(*env)->light = NULL;
	*obj = malloc(sizeof(t_object));
	if (!*obj)
	{
		free(*env);
		exit_with_error("Memory allocation failed", NULL, NULL);
	}
	(*obj)->spheres = NULL;
	(*obj)->planes = NULL;
	(*obj)->cylinders = NULL;
}

int	main(int argc, char **argv)
{
	t_environment	*env;
	t_object		*obj;

	if (argc != 2)
	{
		printf("Usage: %s <scene_file.rt>\n", argv[0]);
		return (1);
	}
	init_structs(&env, &obj);
	parsing_master(argv[1], &env, &obj);
	init_minirt(env, obj);
	return (0);
}
