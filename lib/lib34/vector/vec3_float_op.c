/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_float_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:35:57 by hdelanoe          #+#    #+#             */
/*   Updated: 2019/05/05 15:06:43 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib34.h"

t_vec3	vec3_float_add(t_vec3 *a, float b)
{
	t_vec3	r;

	r.x = a->x + b;
	r.y = a->y + b;
	r.z = a->z + b;
	return (r);
}

t_vec3	vec3_float_subs(t_vec3 *a, float b)
{
	t_vec3	r;

	r.x = a->x - b;
	r.y = a->y - b;
	r.z = a->z - b;
	return (r);
}

t_vec3	vec3_float_mult(t_vec3 a, float b)
{
	t_vec3	r;

	r.x = a.x * b;
	r.y = a.y * b;
	r.z = a.z * b;
	return (r);
}

t_vec3	vec3_float_div(t_vec3 *a, float b)
{
	t_vec3	r;

	r.x = a->x / b;
	r.y = a->y / b;
	r.z = a->z / b;
	return (r);
}
