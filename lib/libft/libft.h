/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 18:17:46 by hdelanoe          #+#    #+#             */
/*   Updated: 2019/05/08 17:41:25 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 1024
# include <string.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

typedef struct		s_stock
{
	int				ret;
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	char			*save;
	char			*rest;
}					t_stock;

double				ft_atod(const char *str);
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
int					ft_isdigit(int c);
void				ft_kill(char *msg);
void				*ft_memalloc(size_t size);
void				*ft_memset(void *s, int c, size_t n);
void				ft_putchar(unsigned char c);
void				ft_putendl(const char *s);
void				ft_putnbr(int n);
void				ft_putstr(const char *s);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dest, const char *src);
void				ft_strdel(char **as);
char				*ft_strdup(const char *s);
char				*ft_strjoin(const char *s1, const char *s2);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnew(size_t size);
char				**ft_strsplit(const char *s, char c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strsub(const char *s, unsigned int start, size_t len);
void				ft_tabfree(char **tab);

int					get_next_line(const int fd, char **line);

#endif
