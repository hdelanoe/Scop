/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib34.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:18:16 by hdelanoe          #+#    #+#             */
/*   Updated: 2019/05/05 15:06:19 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB34_H
# define LIB34_H
# define PI 3.1415926
# include <math.h>

typedef struct s_vec3	t_vec3;
typedef struct s_mat4	t_mat4;

struct					s_vec3
{
	float		x;
	float		y;
	float		z;
};

struct					s_mat4
{
	float		m[4][4];
};

/*
** vec3 **
*/
float					magnitude(t_vec3 v);
float					dot_product(t_vec3 a, t_vec3 b);
t_vec3					vec3(float x, float y, float z);
t_vec3					normalize(t_vec3 a);
t_vec3					vec3_add(t_vec3 a, t_vec3 b);
t_vec3					vec3_subs(t_vec3 a, t_vec3 b);
t_vec3					vec3_mult(t_vec3 a, t_vec3 b);
t_vec3					vec3_float_add(t_vec3 *a, float b);
t_vec3					vec3_float_subs(t_vec3 *a, float b);
t_vec3					vec3_float_mult(t_vec3 a, float b);
t_vec3					vec3_float_div(t_vec3 *a, float b);
/*
** mat4 **
*/
t_mat4					mat4(t_vec3 v);
t_mat4					translate(t_mat4 m, t_vec3 v);
t_mat4					scale(t_vec3 v);
t_mat4					rotate_x(float angle);
t_mat4					rotate_y(float angle);
t_mat4					rotate_z(float angle);
t_mat4					mat4_mult(t_mat4 a, t_mat4 b);
/*
** camera **
*/
t_mat4					look_at(t_vec3 pos, t_vec3 target);
t_mat4					perspective(float angle, float aspect,
									float near, float far);

#endif
