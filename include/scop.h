/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 08:59:40 by hdelanoe          #+#    #+#             */
/*   Updated: 2019/05/07 03:42:02 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H
# define WIDTH 1280
# define HEIGHT 720

# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>

# include "../lib/libft/libft.h"
# include "../lib/lib34/lib34.h"

# include "glad/glad.h"
# include "glfw/glfw3.h"

typedef struct s_env		t_env;
typedef struct s_shader		t_shader;
typedef struct s_texture	t_texture;
typedef struct s_fragment	t_fragment;

struct						s_shader
{
	unsigned int	id;
	unsigned int	vertex;
	unsigned int	fragment;
	const char		*vshader_code;
	const char		*fshader_code;
};

struct						s_texture
{
	unsigned int	id;
	int				width;
	int				height;
	int				size;
	unsigned char	*data;
};

struct						s_fragment
{
	int				*f;
	int				*t;
	int				*n;
};

struct						s_env
{
	GLFWwindow		*win;

	t_shader		model;
	t_shader		light;
	t_texture		texture;

	t_fragment		fragment;
	int				vertex_shader;
	int				fragment_shader;
	int				shader_program;

	float			*vertex;
	float			*coord;
	float			*normal;
	float			*mesh;

	unsigned int	model_vao;
	unsigned int	light_vao;
	unsigned int	model_vbo;
	unsigned int	light_vbo;
	unsigned int	ebo;

	unsigned int	nb_v[2];
	unsigned int	nb_vt[3];
	unsigned int	nb_vn[3];
	unsigned int	nb_f[2];
	unsigned int	frames;

	t_vec3			max;
	t_vec3			min;
	t_vec3			t;
	t_vec3			r;
	t_vec3			s;
	t_vec3			l;

	float			time;
	float			maxi;
	float			mov;

	float			texture_mode;
	bool			wireframe_mode;
	bool			grey_mode;
	bool			light_mode;
	unsigned int	color_mode;
	unsigned int	rotate_mode;

};

void						framebuffer_size_callback(GLFWwindow *window,
												int width, int height);
/*
** shader **
*/
void						init_shader(t_env *env);
void						compile_shader(t_shader *shader);
/*
** texture **
*/
void						init_texture(t_env *env);
void						load_texture(t_texture *texture);
/*
** parsing **
*/
bool						parse_file(t_env *e, char *file);
void						stock_obj(t_env *e, char *file);
void						build_mesh(t_env *env);
/*
** display **
*/
void						display(t_env *env);
void						render(t_env *env, t_mat4 *mvp);
void						recenter(t_env *env);
void						adjust_view(t_env *env);
/*
** input and tools **
*/
void						help(void);
void						reset(t_env *env);
bool						alloc_obj(t_env *e);
void						terminate(char *msg);
void						delete_env(t_env *env);
void						display_parsing(t_env *env);
void						ft_error(t_env *env, char *msg);
void						input(t_env *env, GLFWwindow *window);

#endif
