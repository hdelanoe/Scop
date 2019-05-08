/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 14:04:39 by hdelanoe          #+#    #+#             */
/*   Updated: 2019/05/07 15:49:49 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	read_bmp(t_env *env, const char *filename, t_texture *texture)
{
	int				i;
	FILE			*f;
	unsigned char	header[54];

	if (!(f = fopen(filename, "rb")))
		ft_error(env, "Can't open file");
	if (fread(header, sizeof(unsigned char), 54, f) != 54)
		ft_error(env, "Can't read texture file");
	if (header[0] != 'B' || header[1] != 'M')
		ft_error(env, "Not a bmp file");
	texture->width = *(int*)&header[18];
	texture->height = *(int*)&header[22];
	texture->size = 3 * texture->width * texture->height;
	if (texture->size == 0 || !(texture->data = (unsigned char *)malloc(
					sizeof(unsigned char) * texture->size)))
		ft_error(env, "Couldn't allocate memory for texture data.");
	fread(texture->data, sizeof(unsigned char), texture->size, f);
	fclose(f);
}

void	load_texture(t_texture *texture)
{
	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_2D, texture->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	if (texture->data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height,
				0, GL_BGR, GL_UNSIGNED_BYTE, texture->data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		ft_putendl("Failed to load texture.");
}

void	init_texture(t_env *env)
{
	read_bmp(env, "texture/texture.bmp", &env->texture);
	load_texture(&env->texture);
	glUseProgram(env->model.id);
	glUniform1i(glGetUniformLocation(env->model.id, "myTexture"), 0);
	free(env->texture.data);
}
