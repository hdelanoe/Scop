/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 18:48:14 by hdelanoe          #+#    #+#             */
/*   Updated: 2017/06/04 10:57:55 by hdelanoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned long	i;
	char			*str;

	i = 0;
	str = (char*)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}