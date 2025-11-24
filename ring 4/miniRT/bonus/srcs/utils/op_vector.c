/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprot <cprot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:11:47 by cprot             #+#    #+#             */
/*   Updated: 2025/11/19 16:40:17 by cprot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_vec3	vec_add(t_vec3 va, t_vec3 vb)
{
	t_vec3	result;

	result.x = va.x + vb.x;
	result.y = va.y + vb.y;
	result.z = va.z + vb.z;
	return (result);
}

t_vec3	vec_sub(t_vec3 va, t_vec3 vb)
{
	t_vec3	result;

	result.x = va.x - vb.x;
	result.y = va.y - vb.y;
	result.z = va.z - vb.z;
	return (result);
}

t_vec3	vec_scale(t_vec3 v, double scalar)
{
	t_vec3	result;

	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return (result);
}

t_vec3	vec_mult(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x * b.x;
	result.y = a.y * b.y;
	result.z = a.z * b.z;
	return (result);
}
