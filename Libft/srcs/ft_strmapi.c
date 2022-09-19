/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:27:51 by jalvarad          #+#    #+#             */
/*   Updated: 2021/05/31 17:29:04 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*aux;
	size_t	s_len;
	size_t	i;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	i = 0;
	aux = malloc(sizeof(char) * s_len + 1);
	if (!aux)
		return (NULL);
	while (i < s_len)
	{
		aux[i] = (*f)(i, s[i]);
		i++;
	}
	aux[s_len] = '\0';
	return (aux);
}
