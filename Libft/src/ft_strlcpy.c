/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:26:02 by jalvarad          #+#    #+#             */
/*   Updated: 2021/05/31 17:26:53 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	a;
	size_t	b;

	a = 0;
	if (!src)
		return (0);
	if (size > 0)
	{
		while (src[a] && a < size - 1)
		{
			dst[a] = src [a];
			a++;
		}
	}
	if (size != 0)
		dst[a] = 0;
	b = 0;
	while (src[b] != '\0')
		b++;
	return (b);
}
