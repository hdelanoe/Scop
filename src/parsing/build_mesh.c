/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_mesh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:16:10 by hdelanoe          #+#    #+#             */
/*   Updated: 2019/05/07 03:39:14 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/scop.h"

void	mesh_coord(float *tmp, t_env *e, int i)
{
	float maxu;
	float maxv;

	maxu = e->max.x - e->min.x > e->max.y - e->min.y ? e->max.x : e->max.y;
	maxv = maxu;
	maxu = maxu > e->max.z - e->min.z ? maxu : e->max.z;
	maxv = maxv < e->max.z - e->min.z ? maxv : e->max.z;
	if (e->nb_vt[1] && e->fragment.t[i] != -1)
	{
		tmp[e->fragment.f[i] * 8 + 6] = e->coord[e->fragment.t[i] * 3];
		tmp[e->fragment.f[i] * 8 + 7] = e->coord[e->fragment.t[i] * 3 + 1];
	}
	else
	{
		tmp[e->fragment.f[i] * 8 + 6] = \
		e->vertex[e->fragment.f[i] * 3] < 0 ? \
		e->vertex[e->fragment.f[i] * 3] / (maxu * 2) - 0.5 : \
		e->vertex[e->fragment.f[i] * 3] / (maxu * 2) + 0.5;
		tmp[e->fragment.f[i] * 8 + 7] = \
		e->vertex[e->fragment.f[i] * 3 + 1] < 0 ? \
		e->vertex[e->fragment.f[i] * 3 + 1] / (maxv * 2) - 0.5 : \
		e->vertex[e->fragment.f[i] * 3 + 1] / (maxv * 2) + 0.5;
	}
}

void	comput_colors(float *tmp, t_env *e, int i)
{
	int		j;
	t_vec3	c[6];

	j = e->fragment.f[i];
	c[0] = vec3(0.69, 0.21, 0.57);
	c[1] = vec3(0.29, 0.79, 0.45);
	c[2] = vec3(0.12, 0.37, 0.85);
	c[3] = vec3(0.86, 0.66, 0.12);
	c[4] = vec3(0.69 - 0.29, 0.21 - 0.79, 0.57 - 0.45);
	c[5] = vec3(0.12 - 0.86, 0.37 - 0.66, 0.85 - 0.12);
	tmp[j * 8 + 3] = ((c[0].x + c[2].x) / 2)
	+ (((e->vertex[j * 3] / e->max.x * c[4].x)
		+ ((e->vertex[j * 3] / e->max.y * c[5].x)) / 2));
	tmp[j * 8 + 4] = ((c[0].y + c[2].y) / 2)
	+ (((e->vertex[j * 3 + 1] / e->max.x * c[4].y)
		+ ((e->vertex[j * 3 + 1] / e->max.y * c[5].y)) / 2));
	tmp[j * 8 + 5] = ((c[0].z + c[2].z) / 2)
	+ (((e->vertex[j * 3 + 2] / e->max.x * c[4].z)
		+ ((e->vertex[j * 3 + 2] / e->max.y * c[5].z)) / 2));
}

void	mesh_color(float *tmp, t_env *e, int i)
{
	int		j;

	j = e->fragment.f[i];
	if (e->nb_vn[1] && e->fragment.t[i] != -1)
	{
		tmp[j * 8 + 3] = \
		e->normal[e->fragment.n[i] * 3];
		tmp[j * 8 + 4] = \
		e->normal[e->fragment.n[i] * 3 + 1];
		tmp[j * 8 + 5] = \
		e->normal[e->fragment.n[i] * 3 + 2];
	}
	else
		comput_colors(tmp, e, i);
}

void	mesh(float *tmp, t_env *e, int i)
{
	tmp[e->fragment.f[i] * 8] = e->vertex[e->fragment.f[i] * 3];
	tmp[e->fragment.f[i] * 8 + 1] = e->vertex[e->fragment.f[i] * 3 + 1];
	tmp[e->fragment.f[i] * 8 + 2] = e->vertex[e->fragment.f[i] * 3 + 2];
	mesh_color(tmp, e, i);
	mesh_coord(tmp, e, i);
}

void	build_mesh(t_env *env)
{
	int	i;
	int	new;

	recenter(env);
	adjust_view(env);
	new = env->nb_v[1] * 3;
	if (!(env->mesh = (float*)malloc(sizeof(float*) * new)))
		ft_error(env, "Can't malloc mesh.");
	i = -1;
	while (++i < env->nb_f[1])
		mesh(env->mesh, env, i);
	free(env->vertex);
	env->vertex = env->mesh;
	env->nb_v[1] = new;
}
