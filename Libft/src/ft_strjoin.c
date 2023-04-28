/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:20:02 by jalvarad          #+#    #+#             */
/*   Updated: 2021/05/31 17:22:35 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		n;
	int		a;
	int		len;
	char	*aux_s1;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	n = 0;
	a = 0;
	aux_s1 = malloc(sizeof(char) * len + 1);
	if (!aux_s1)
		return (0);
	ft_memcpy(aux_s1, s1, ft_strlen(s1) + 1);
	while (aux_s1[a] != '\0')
		a++;
	while (s2[n] != '\0')
	{
		aux_s1[a + n] = s2[n];
		n++;
	}
	aux_s1[a + n] = '\0';
	return (aux_s1);
}
