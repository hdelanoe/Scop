/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:15:39 by hdelanoe          #+#    #+#             */
/*   Updated: 2019/05/07 03:39:43 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	c_mode(t_env *env, GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		env->texture_mode -= env->texture_mode <= 0 ? 0 : 0.01f;
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		env->texture_mode += env->texture_mode >= 1 ? 0 : 0.01f;
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
	{
		env->color_mode = 0;
		env->grey_mode = false;
	}
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
		env->grey_mode = true;
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
		env->color_mode = 1;
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
		env->color_mode = 2;
	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
		env->color_mode = 3;
}

void	mode(t_env *env, GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		reset(env);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
		env->rotate_mode = 0;
	if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)
		env->rotate_mode = 1;
	if (glfwGetKey(window, GLFW_KEY_BACKSLASH) == GLFW_PRESS)
		env->rotate_mode = 2;
	if (glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS)
		env->rotate_mode = 3;
	c_mode(env, window);
}

void	movement(t_env *env, GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		env->t.x -= env->mov;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		env->t.x += env->mov;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		env->t.y -= env->mov;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		env->t.y += env->mov;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		env->t.z += env->mov;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		env->t.z -= env->mov;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		env->r.x += 0.02f;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		env->r.x -= 0.02f;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		env->r.y -= 0.02f;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		env->r.y += 0.02f;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		env->r.z -= 0.02f;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		env->r.z += 0.02f;
}

void	light(t_env *env, GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		env->l.x += env->l.x <= env->maxi * 5 ? 10 * env->mov : 0;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		env->l.x -= -env->l.x <= env->maxi * 5 ? 10 * env->mov : 0;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		env->l.y += env->l.y <= env->maxi * 5 ? 10 * env->mov : 0;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		env->l.y -= -env->l.y <= env->maxi * 5 ? 10 * env->mov : 0;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		env->l.z += env->l.z <= env->maxi * 10 ? 20 * env->mov : 0;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		env->l.z -= -env->l.z <= env->maxi * 10 ? 20 * env->mov : 0;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		env->light_mode = true;
	else
		env->light_mode = false;
}

void	input(t_env *env, GLFWwindow *window)
{
	mode(env, window);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		light(env, window);
	else
		movement(env, window);
	if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)
		env->s = vec3(env->s.x + env->mov,
				env->s.y + env->mov,
				env->s.z + env->mov);
	if (env->s.x >= -1
			&& glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS)
		env->s = vec3(env->s.x - env->mov,
				env->s.y - env->mov,
				env->s.z - env->mov);
	if (env->rotate_mode == 0)
		env->r.y += 0.01f;
	else if (env->rotate_mode == 1)
		env->r.x += 0.01f;
	else if (env->rotate_mode == 2)
		env->r.z += 0.01f;
}
