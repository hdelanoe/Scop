/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 09:43:36 by hdelanoe          #+#    #+#             */
/*   Updated: 2019/05/05 14:53:20 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib34.h"

t_mat4	look_at(t_vec3 pos, t_vec3 target)
{
	t_vec3 f;
	t_vec3 s;
	t_vec3 u;
	t_mat4 r;

	f = normalize(vec3_subs(target, pos));
	s = normalize(vec3_mult(vec3(0, 1, 0), f));
	u = vec3_mult(f, s);
	r.m[0][0] = s.x;
	r.m[0][1] = s.y;
	r.m[0][2] = s.z;
	r.m[0][3] = 0.f;
	r.m[1][0] = u.x;
	r.m[1][1] = u.y;
	r.m[1][2] = u.z;
	r.m[1][3] = 0.f;
	r.m[2][0] = f.x;
	r.m[2][1] = f.y;
	r.m[2][2] = f.z;
	r.m[2][3] = 0.f;
	r.m[3][0] = dot_product(s, pos);
	r.m[3][1] = dot_product(u, pos);
	r.m[3][2] = dot_product(f, pos);
	r.m[3][3] = 1.0f;
	return (r);
}

t_mat4	perspective(float angle, float aspect, float near, float far)
{
	t_mat4	r;
	float	scale;

	scale = 1 / tanf(angle / 4);
	r = mat4(vec3(1, 1, 1));
	r.m[0][0] = scale / aspect;
	r.m[1][1] = scale;
	r.m[2][2] = -(far + near) / (far - near) * -1;
	r.m[2][3] = -1.0f;
	r.m[3][2] = -(2 * far * near) / (far - near) * -1;
	r.m[3][3] = 0.f;
	return (r);
}
