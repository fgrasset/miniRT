/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabien <fabien@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:43:18 by fabien            #+#    #+#             */
/*   Updated: 2023/08/15 18:43:21 by fabien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

t_v4d	new_v4d(double x, double y, double z, double w)
{
	t_v4d	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = w;
	return (v);
}

t_v4d	v4d_from_v3d(t_v3d v, double w)
{
	return (new_v4d(v.x, v.y, v.z, w));
}

t_v3d	v4d_to_v3d(t_v4d v)
{
	t_v3d	result;

	result = new_v3d(v.x, v.y, v.z);
	return (result);
}

t_v4d	mat4_mul_v4d(t_mat4 m, t_v4d v)
{
	t_v4d	result;

	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y \
	+ m.m[0][2] * v.z + m.m[0][3] * v.w;
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y \
	+ m.m[1][2] * v.z + m.m[1][3] * v.w;
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y \
	+ m.m[2][2] * v.z + m.m[2][3] * v.w;
	result.w = m.m[3][0] * v.x + m.m[3][1] * v.y \
	+ m.m[3][2] * v.z + m.m[3][3] * v.w;
	return (result);
}
