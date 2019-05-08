/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:14:52 by hdelanoe          #+#    #+#             */
/*   Updated: 2019/05/07 16:10:07 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/scop.h"

void	delete_env(t_env *env)
{
	free(env->vertex);
	free(env->coord);
	free(env->normal);
	free(env->fragment.f);
	free(env->fragment.t);
	free(env->fragment.n);
	glDeleteVertexArrays(1, &env->model_vao);
	glDeleteVertexArrays(1, &env->light_vao);
	glDeleteBuffers(1, &env->model_vbo);
	glDeleteBuffers(1, &env->light_vbo);
	glDeleteBuffers(1, &env->ebo);
	glfwTerminate();
}

void	framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

t_env	*init(t_env *env)
{
	env->time = glfwGetTime();
	env->frames = 0.0f;
	if (!glfwInit())
		ft_error(env, "Unable to init GLFW");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	if (!(env->win = glfwCreateWindow(WIDTH, HEIGHT, "Scop", NULL, NULL)))
		ft_error(env, "Unable to create window");
	glfwMakeContextCurrent(env->win);
	glfwSetFramebufferSizeCallback(env->win, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		ft_error(env, "Unable to load glad.");
	glEnable(GL_DEPTH_TEST);
	return (env);
}

void	render_loop(t_env *env)
{
	env->time = glfwGetTime();
	env->frames = 0.0f;
	while (!glfwWindowShouldClose(env->win))
	{
		input(env, env->win);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		display(env);
		glfwSwapBuffers(env->win);
		glfwPollEvents();
	}
}

int		main(int argc, char **argv)
{
	t_env env;

	if (argc != 2)
		help();
	if (!ft_strstr(argv[1], ".obj"))
		ft_kill("file is not a .obj");
	ft_bzero(&env, sizeof(env));
	if (!(parse_file(&env, argv[1])) || !(alloc_obj(&env)))
		ft_kill("malloc error.");
	init(&env);
	stock_obj(&env, argv[1]);
	display_parsing(&env);
	build_mesh(&env);
	init_shader(&env);
	init_texture(&env);
	render_loop(&env);
	delete_env(&env);
	return (0);
}
