/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:29:58 by jalvarad          #+#    #+#             */
/*   Updated: 2021/05/31 16:31:07 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			a;
	unsigned char	*p;

	a = 0;
	p = (unsigned char *)s;
	while (a < n)
	{
		if ((unsigned char)c == p[a])
			return ((unsigned char *) s);
		a++;
		s++;
	}
	return (NULL);
}
