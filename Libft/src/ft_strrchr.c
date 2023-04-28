/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:36:22 by jalvarad          #+#    #+#             */
/*   Updated: 2021/05/31 17:36:33 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c )
{
	int		len_s;
	char	*aux_s;

	aux_s = (char *)s;
	len_s = ft_strlen(s);
	while (len_s >= 0)
	{
		if (aux_s[len_s] == (char)c)
			return (aux_s + len_s);
		len_s--;
	}
	return (NULL);
}
