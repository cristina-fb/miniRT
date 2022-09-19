/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:17:40 by jalvarad          #+#    #+#             */
/*   Updated: 2021/05/31 17:19:43 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*aux_s1;

	aux_s1 = malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!aux_s1)
		return (0);
	ft_memcpy(aux_s1, s1, ft_strlen(s1));
	aux_s1[ft_strlen(s1)] = 0;
	return (aux_s1);
}
