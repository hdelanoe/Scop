/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 06:21:20 by hdelanoe          #+#    #+#             */
/*   Updated: 2019/05/07 15:50:13 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	fps_counter(t_env *env)
{
	float	current;

	current = glfwGetTime();
	env->frames++;
	if (current - env->time >= 1.0f)
	{
		ft_putstr("FPS: ");
		ft_putnbr(env->frames);
		ft_putchar('\n');
		env->time += 1.0f;
		env->frames = 0;
	}
}

void	recenter(t_env *e)
{
	int		i;
	t_vec3	diff;

	i = 0;
	while (i < e->nb_v[1])
	{
		e->max.x = e->vertex[i] > e->max.x ? e->vertex[i] : e->max.x;
		e->max.y = e->vertex[i + 1] > e->max.y ? e->vertex[i + 1] : e->max.y;
		e->max.z = e->vertex[i + 2] > e->max.z ? e->vertex[i + 2] : e->max.z;
		e->min.x = e->vertex[i] < e->min.x ? e->vertex[i] : e->min.x;
		e->min.y = e->vertex[i + 1] < e->min.y ? e->vertex[i + 1] : e->min.y;
		e->min.z = e->vertex[i + 2] < e->min.z ? e->vertex[i + 2] : e->min.z;
		i += 3;
	}
	diff = vec3((e->max.x - e->min.x) / 2,
		(e->max.y - e->min.y) / 2,
		(e->max.z - e->min.z) / 2);
	i = 0;
	while (i < e->nb_v[1])
	{
		e->vertex[i] = +diff.x + e->vertex[i] - e->max.x;
		e->vertex[i + 1] = +diff.y + e->vertex[i + 1] - e->max.y;
		e->vertex[i + 2] = +diff.z + e->vertex[i + 2] - e->max.z;
		i += 3;
	}
}

void	adjust_view(t_env *env)
{
	env->maxi = env->max.x - env->min.x > env->max.y - env->min.y ? \
	env->max.x : env->max.y;
	env->maxi = env->maxi > env->max.z - env->min.z ? \
	env->maxi : env->max.z;
	env->mov = env->maxi / 100;
	env->t.z = -2 * env->maxi;
}

void	render(t_env *env, t_mat4 *mvp)
{
	glUseProgram(env->model.id);
	glBindVertexArray(env->model_vao);
	glUniformMatrix4fv(glGetUniformLocation(env->model.id,
				"mvp"), 1, GL_FALSE, &mvp[3].m[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(env->model.id,
				"model"), 1, GL_FALSE, &mvp[2].m[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(env->model.id,
				"lightPos"), 1, GL_FALSE, &mvp[4].m[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(env->model.id,
				"viewPos"), 1, GL_FALSE, &mvp[0].m[0][0]);
	glUniform1f(glGetUniformLocation(env->model.id,
				"textureMode"), env->texture_mode);
	glUniform1i(glGetUniformLocation(env->model.id,
				"lightMode"), env->light_mode);
	glUniform1f(glGetUniformLocation(env->model.id,
				"colorMode"), env->color_mode);
	glUniform1i(glGetUniformLocation(env->model.id,
				"greyMode"), env->grey_mode);
	glDrawElements(GL_TRIANGLES, env->nb_f[1], GL_UNSIGNED_INT, 0);
	glUseProgram(env->light.id);
	glBindVertexArray(env->light_vao);
	glUniformMatrix4fv(glGetUniformLocation(env->light.id,
				"mvp"), 1, GL_FALSE, &mvp[4].m[0][0]);
}

void	display(t_env *env)
{
	t_mat4	t_matrix[2];
	t_mat4	r_matrix[4];
	t_mat4	s_matrix;
	t_mat4	mvp[5];

	t_matrix[0] = translate(mat4(vec3(1, 1, 1)),
			vec3(env->t.x, env->t.y, env->t.z));
	t_matrix[1] = translate(t_matrix[0],
			vec3(env->l.x, env->l.y, env->l.z));
	r_matrix[0] = rotate_x(env->r.x);
	r_matrix[1] = rotate_y(env->r.y);
	r_matrix[2] = rotate_z(env->r.z);
	r_matrix[3] = mat4_mult(mat4_mult(r_matrix[0], r_matrix[2]), r_matrix[1]);
	s_matrix = scale(vec3(env->s.x + 1, env->s.y + 1, env->s.z + 1));
	mvp[0] = look_at(vec3(0, 0, 10), vec3(0, 0, 0));
	mvp[1] = perspective(PI / 8, WIDTH / HEIGHT, 1.f, 100.0f);
	mvp[2] = mat4_mult(mat4_mult(t_matrix[0], r_matrix[3]), s_matrix);
	mvp[3] = mat4_mult(mat4_mult(mvp[0], mvp[1]), mvp[2]);
	mvp[4] = mat4_mult(mat4_mult(mvp[0], mvp[1]), t_matrix[1]);
	render(env, mvp);
	fps_counter(env);
}
