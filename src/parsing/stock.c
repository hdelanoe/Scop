/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 19:34:35 by hdelanoe          #+#    #+#             */
/*   Updated: 2019/05/07 15:49:21 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

unsigned int	stock_vertex(char *buff, float *container, unsigned int nb)
{
	int		i;
	char	**tmp;

	i = -1;
	tmp = ft_strsplit(buff, ' ');
	while (tmp[++i])
		container[nb + i] = (float)(ft_atod(tmp[i]));
	ft_tabfree(tmp);
	return (i);
}

void			choose_attribut(t_env *e, char *tmp)
{
	if (tmp && e->nb_vt[0]
		&& abs((ft_atoi(tmp) - 1)) < e->nb_vt[0] / 3
		&& abs((ft_atoi(tmp) - 1)) >= 0)
	{
		e->fragment.t[e->nb_f[1]] = abs((ft_atoi(tmp) - 1));
		e->fragment.n[e->nb_f[1]] = -1;
	}
	else if (tmp && e->nb_vn[0]
		&& abs((ft_atoi(tmp) - 1)) < e->nb_vn[0] / 3
		&& abs((ft_atoi(tmp) - 1)) >= 0)
	{
		e->fragment.n[e->nb_f[1]] = abs((ft_atoi(tmp) - 1));
		e->fragment.t[e->nb_f[1]] = -1;
	}
	else
	{
		e->fragment.t[e->nb_f[1]] = -1;
		e->fragment.n[e->nb_f[1]] = -1;
	}
}

void			stock_fragment(t_env *e, char *buff)
{
	char	**tmp;

	tmp = ft_strsplit(buff, '/');
	if (tmp[0] && abs(ft_atoi(tmp[0]) - 1) < e->nb_v[0] / 3)
		e->fragment.f[e->nb_f[1]] = abs((ft_atoi(tmp[0]) - 1));
	else
		ft_error(e, "Parsing error. stock_fragment");
	if (tmp[1] && tmp[2])
	{
		e->fragment.t[e->nb_f[1]] = abs((ft_atoi(tmp[1]) - 1)) < e->nb_vt[0] / 3
		&& abs((ft_atoi(tmp[1]) - 1)) >= 0 ? abs((ft_atoi(tmp[1]) - 1)) : -1;
		e->fragment.n[e->nb_f[1]] = abs((ft_atoi(tmp[2]) - 1)) < e->nb_vt[0] / 3
		&& abs((ft_atoi(tmp[2]) - 1)) >= 0 ? abs((ft_atoi(tmp[2]) - 1)) : -1;
	}
	else
		choose_attribut(e, tmp[1]);
	e->nb_f[1]++;
	ft_tabfree(tmp);
}

void			parse_fragment(t_env *e, char *buff)
{
	int		i;
	int		offset;
	char	**tmp;

	i = -1;
	offset = 0;
	tmp = ft_strsplit(buff, ' ');
	while (tmp[++i])
	{
		if (i >= 3 && tmp[i])
		{
			offset++;
			stock_fragment(e, tmp[0]);
			stock_fragment(e, tmp[offset + 1]);
			stock_fragment(e, tmp[offset + 2]);
		}
		else if (tmp[i])
			stock_fragment(e, tmp[i]);
	}
	ft_tabfree(tmp);
}

void			stock_obj(t_env *e, char *file)
{
	int		i;
	int		fd;
	char	*buff;

	if ((fd = open(file, O_RDONLY)) < 0)
		ft_error(e, "Cant open file.");
	while (get_next_line(fd, &buff) == 1)
	{
		i = -1;
		if (buff[0] == 'v')
		{
			if (buff[1] == ' ')
				e->nb_v[1] += stock_vertex(&buff[2], e->vertex, e->nb_v[1]);
			else if (buff[1] == 't' && buff[2] == ' ')
				e->nb_vt[1] += stock_vertex(&buff[3], e->coord, e->nb_vt[1]);
			else if (buff[1] == 'n' && buff[2] == ' ')
				e->nb_vn[1] += stock_vertex(&buff[3], e->normal, e->nb_vn[1]);
		}
		else if (buff[0] == 'f' && buff[1] == ' ')
			parse_fragment(e, &buff[2]);
		free(buff);
	}
	close(fd);
}
