/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:03:30 by jalvarad          #+#    #+#             */
/*   Updated: 2022/12/26 15:21:02 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
/* this function returns char ** with the RGB */
/* solo retorna NULL en caso de fallo de malloc */

static short int	*save_rgb(char **rgb_buf, bool *err)
{
	short int	*rgb;
	short int	i;

	rgb = ft_calloc(3, sizeof(short int));
	i = -1;
	if (!rgb)
	{
		*err = true;
		return (NULL);
	}
	rgb[0] = ft_mod_atof(rgb_buf[0], err);
	rgb[1] = ft_mod_atof(rgb_buf[1], err);
	rgb[2] = ft_mod_atof(rgb_buf[2], err);
	while (++i < 3 && !*err)
		*err = (rgb[i] < 0 || rgb[i] > 255);
	return (rgb);
}

short int	*get_rgb(char *attr_buf, bool *err)
{
	char		**rgb_buf;
	short int	*rgb;

	rgb_buf = ft_split(attr_buf, ',');
	if (!str_is_float(rgb_buf[0]) || !str_is_float(rgb_buf[1]) || \
		!str_is_float(rgb_buf[2]))
		*err = true;
	rgb = save_rgb(rgb_buf, err);
	ft_free_matrix(rgb_buf);
	return (rgb);
}
