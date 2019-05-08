/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:28:30 by hdelanoe          #+#    #+#             */
/*   Updated: 2019/05/01 19:28:32 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib34.h"

t_vec3	vec3(float x, float y, float z)
{
	t_vec3 v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

float	magnitude(t_vec3 a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3	normalize(t_vec3 a)
{
	t_vec3	na;
	float	magn;

	magn = magnitude(a);
	na.x = a.x / magn;
	na.y = a.y / magn;
	na.z = a.z / magn;
	return (na);
}
