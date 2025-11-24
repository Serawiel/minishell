/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vec_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:11:41 by cprot             #+#    #+#             */
/*   Updated: 2025/11/19 16:40:15 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

double	vec_dot(t_vec3 va, t_vec3 vb)
{
	return (va.x * vb.x + va.y * vb.y + va.z * vb.z);
}

double	vec_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	vec_normalize(t_vec3 v)
{
	double	length;
	t_vec3	result;

	length = vec_length(v);
	if (length == 0)
		return (v);
	result.x = v.x / length;
	result.y = v.y / length;
	result.z = v.z / length;
	return (result);
}

t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vec3	vec_perp_to_axis(t_vec3 v, t_vec3 axis)
{
	double	projection_scalaire;
	t_vec3	v_parallel;
	t_vec3	v_perp;

	projection_scalaire = vec_dot(v, axis);
	v_parallel = vec_scale(axis, projection_scalaire);
	v_perp = vec_sub(v, v_parallel);
	return (v_perp);
}
