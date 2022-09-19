/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:52:50 by jalvarad          #+#    #+#             */
/*   Updated: 2021/05/31 16:56:25 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d_aux;
	const unsigned char	*s_aux;

	d_aux = ((unsigned char *)dst);
	s_aux = ((const unsigned char *)src);
	if (d_aux == s_aux)
		return (dst);
	else if (d_aux > s_aux)
	{
		while (len)
		{
			d_aux[len - 1] = s_aux[len - 1];
			len--;
		}
		return (dst);
	}
	else
		return (ft_memcpy(d_aux, s_aux, len));
}
