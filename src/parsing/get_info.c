/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:49:32 by hdelanoe          #+#    #+#             */
/*   Updated: 2019/05/07 00:23:40 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		get_vertex(char *line)
{
	int		i;
	char	**tmp;

	if (line[0] == 'v' && line[1] == ' ')
	{
		if (!(tmp = ft_strsplit(&line[3], ' ')))
			return (-1);
		i = 0;
		while (tmp[i])
			i++;
		ft_tabfree(tmp);
		if (i != 3)
			ft_kill("Parsing error. get_vertex");
		return (3);
	}
	return (0);
}

int		get_normal(char *line)
{
	int		i;
	char	**tmp;

	if (line[0] == 'v' && line[1] == 'n' && line[2] == ' ')
	{
		if (!(tmp = ft_strsplit(&line[3], ' ')))
			return (-1);
		i = 0;
		while (tmp[i])
			i++;
		ft_tabfree(tmp);
		if (i != 3)
			ft_kill("Parsing error. get_normal");
		return (3);
	}
	return (0);
}

int		get_texture(char *line)
{
	int		i;
	char	**tmp;

	if (line[0] == 'v' && line[1] == 't' && line[2] == ' ')
	{
		if (!(tmp = ft_strsplit(&line[3], ' ')))
			return (-1);
		i = 0;
		while (tmp[i])
			i++;
		ft_tabfree(tmp);
		if (i < 2 || i > 3)
			ft_kill("Parsing error. get_texture");
		return (i);
	}
	return (0);
}

int		get_fragment(char *line)
{
	int		i;
	char	**tmp;

	if (line[0] == 'f' && line[1] == ' ')
	{
		if (!(tmp = ft_strsplit(&line[2], ' ')))
			return (-1);
		i = 0;
		while (tmp[i])
			i++;
		ft_tabfree(tmp);
		if (i >= 3)
			return (3 + (i - 3) * 3);
		else
			ft_kill("Parsing error. get_fragment");
	}
	return (0);
}

bool	parse_file(t_env *e, char *file)
{
	int		fd;
	int		i;
	char	*buff;

	if ((fd = open(file, O_RDWR)) < 0)
		ft_kill("Cant open file.");
	ft_putendl("Waiting for parsing...");
	while (get_next_line(fd, &buff) == 1)
	{
		if ((i = get_vertex(buff)) == -1)
			return (false);
		e->nb_v[0] += i;
		if ((i = get_texture(buff)) == -1)
			return (false);
		e->nb_vt[0] += i;
		if ((i = get_normal(buff)) == -1)
			return (false);
		e->nb_vn[0] += i;
		if ((i = get_fragment(buff)) == -1)
			return (false);
		e->nb_f[0] += i;
		free(buff);
	}
	close(fd);
	return (true);
}
