/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 08:54:29 by hdelanoe          #+#    #+#             */
/*   Updated: 2019/05/05 14:58:02 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib34.h"

t_mat4	rotate_x(float angle)
{
	t_mat4 m;

	m = mat4(vec3(1, 1, 1));
	m.m[1][1] = cosf(angle);
	m.m[1][2] = -sinf(angle);
	m.m[2][1] = sinf(angle);
	m.m[2][2] = cosf(angle);
	return (m);
}

t_mat4	rotate_y(float angle)
{
	t_mat4 m;

	m = mat4(vec3(1, 1, 1));
	m.m[0][0] = cosf(angle);
	m.m[0][2] = sinf(angle);
	m.m[2][0] = -sinf(angle);
	m.m[2][2] = cosf(angle);
	return (m);
}

t_mat4	rotate_z(float angle)
{
	t_mat4 m;

	m = mat4(vec3(1, 1, 1));
	m.m[0][0] = cosf(angle);
	m.m[0][1] = -sinf(angle);
	m.m[1][0] = sinf(angle);
	m.m[1][1] = cosf(angle);
	return (m);
}
