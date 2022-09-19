/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:39:51 by jalvarad          #+#    #+#             */
/*   Updated: 2021/05/31 17:43:16 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	ps;
	char	*aux_s;

	ps = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s) - 1)
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start - 1)
		len = ft_strlen(s) - start ;
	aux_s = malloc(sizeof(char) * len + 1);
	if (!aux_s)
		return (0);
	while (s)
	{
		if (ps >= start)
		{
			ft_memcpy(aux_s, s + ps, len);
			break ;
		}
		ps++;
	}
	aux_s[len] = 0;
	return (aux_s);
}
