/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:41:46 by hdelanoe          #+#    #+#             */
/*   Updated: 2019/05/07 15:36:40 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	help(void)
{
	ft_putendl("USAGE: ./scop [FILE.obj]");
	ft_putendl("------------------------");
	ft_putendl("'W', 'A', 'S', 'D', 'Q', 'E' to translate the model.");
	ft_putendl("'I', 'J', 'K', 'L', 'U', 'O' to rotate the model.");
	ft_putendl("'SPACE' enable lightMode");
	ft_putendl("Add 'LEFT_SHIFT' for control the light with 'IJKL'.");
	ft_putendl("'1', '2', '3' to switch between \
			wireframe, filled, and point vertex.");
	ft_putendl("'4', '5' for the texture alpha.");
	ft_putendl("'7', '8', '9' and 0 for colorMode.");
	ft_putendl("'DELETE' for toggle auto-rotation");
	ft_putendl("'[', ']', '\\' to switch between auto-rotation.");
	ft_putendl("',' and '.' to zoom.");
	ft_kill("------------------------");
}

void	reset(t_env *env)
{
	env->t.x = 0;
	env->t.y = 0;
	env->t.z = -2 * env->maxi;
	env->r.x = 0;
	env->r.y = 0;
	env->r.z = 0;
	env->s.x = 0;
	env->s.y = 0;
	env->s.z = 0;
	env->l.x = 0;
	env->l.y = 0;
	env->l.z = 0;
	env->texture_mode = 0;
	env->wireframe_mode = 0;
	env->light_mode = 0;
	env->rotate_mode = 0;
	env->color_mode = 0;
	env->grey_mode = 0;
}

void	display_parsing(t_env *env)
{
	ft_putstr("vertex : ");
	ft_putnbr(env->nb_v[1] / 3);
	ft_putchar('\n');
	ft_putstr("polygons : ");
	ft_putnbr(env->nb_f[1] / 3);
	ft_putchar('\n');
	if (env->nb_vt[1])
		ft_putendl("texture map: true");
	else
		ft_putendl("texture map: false");
	if (env->nb_vn[1])
		ft_putendl("normal map: true");
	else
		ft_putendl("normal map: false");
}

bool	alloc_obj(t_env *e)
{
	if (!(e->vertex = (float*)malloc(sizeof(float*) * e->nb_v[0])))
		return (false);
	if (!(e->coord = (float*)malloc(sizeof(float*) * e->nb_vt[0])))
		return (false);
	if (!(e->normal = (float*)malloc(sizeof(float*) * e->nb_vn[0])))
		return (false);
	if (!(e->fragment.f = (int*)malloc(sizeof(int*) * e->nb_f[0])))
		return (false);
	if (!(e->fragment.t = (int*)malloc(sizeof(int*) * e->nb_f[0])))
		return (false);
	if (!(e->fragment.n = (int*)malloc(sizeof(int*) * e->nb_f[0])))
		return (false);
	return (true);
}

void	ft_error(t_env *env, char *msg)
{
	delete_env(env);
	ft_kill(msg);
}
