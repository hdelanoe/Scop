/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:32:50 by hdelanoe          #+#    #+#             */
/*   Updated: 2019/05/07 00:23:16 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	compile_shader(t_shader *shader)
{
	char	info_log[512];
	int		success;

	shader->vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader->vertex, 1, &shader->vshader_code, NULL);
	glCompileShader(shader->vertex);
	glGetShaderiv(shader->vertex, GL_COMPILE_STATUS, &success);
	if (!success)
		glGetShaderInfoLog(shader->vertex, 512, NULL, info_log);
	shader->fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader->fragment, 1, &shader->fshader_code, NULL);
	glCompileShader(shader->fragment);
	glGetShaderiv(shader->fragment, GL_COMPILE_STATUS, &success);
	if (!success)
		glGetShaderInfoLog(shader->fragment, 512, NULL, info_log);
	shader->id = glCreateProgram();
	glAttachShader(shader->id, shader->vertex);
	glAttachShader(shader->id, shader->fragment);
	glLinkProgram(shader->id);
	glGetProgramiv(shader->id, GL_LINK_STATUS, &success);
	if (!success)
		glGetProgramInfoLog(shader->id, 512, NULL, info_log);
	glDeleteShader(shader->vertex);
	glDeleteShader(shader->fragment);
}

char	*set_code(t_env *env, char *file)
{
	FILE	*fp;
	size_t	len;
	char	*buff;

	if (!(fp = fopen(file, "r")))
		ft_error(env, "Cant open shader file.");
	fseek(fp, 0L, SEEK_END);
	len = ftell(fp);
	rewind(fp);
	if (!(buff = calloc(1, len + 1)))
		ft_error(env, "shader memory allocation fails");
	if (fread(buff, len, 1, fp) != 1)
		ft_error(env, "read shader file fails");
	fclose(fp);
	return (buff);
}

void	bind_model(t_env *env)
{
	glGenVertexArrays(1, &env->model_vao);
	glBindVertexArray(env->model_vao);
	glGenBuffers(1, &env->model_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, env->model_vbo);
	glBufferData(GL_ARRAY_BUFFER,
			sizeof(GL_FLOAT) * env->nb_v[1], env->vertex, GL_STATIC_DRAW);
	glGenBuffers(1, &env->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			sizeof(GL_FLOAT) * env->nb_f[1], env->fragment.f, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
			8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
			8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void	init_shader(t_env *env)
{
	float	light_arr[3];

	ft_bzero(light_arr, sizeof(env));
	env->model.vshader_code = set_code(env, "src/shader/1.0.model.vs");
	env->model.fshader_code = set_code(env, "src/shader/1.0.model.fs");
	env->light.vshader_code = set_code(env, "src/shader/1.0.light.vs");
	env->light.fshader_code = set_code(env, "src/shader/1.0.light.fs");
	compile_shader(&env->model);
	compile_shader(&env->light);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, env->texture.id);
	bind_model(env);
	glGenVertexArrays(1, &env->light_vao);
	glBindVertexArray(env->light_vao);
	glGenBuffers(1, &env->light_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, env->light_vbo);
	glBufferData(GL_ARRAY_BUFFER,
			sizeof(GL_FLOAT) * 3, light_arr, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}
