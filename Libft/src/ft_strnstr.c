/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:30:58 by jalvarad          #+#    #+#             */
/*   Updated: 2021/05/31 17:35:04 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	a;
	size_t	b;

	if (!*(needle))
		return ((char *)haystack);
	if (!*(haystack))
		return (0);
	a = 0;
	while (haystack[a] != 0)
	{
		b = 0;
		while (needle[b] == haystack[a + b] && b < len)
		{
			if (needle[b + 1] == 0 && a + b < len)
				return ((char *)haystack + a);
			b++;
		}
		a++;
	}
	return (0);
}
