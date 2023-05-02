/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:03:30 by jalvarad          #+#    #+#             */
/*   Updated: 2023/05/02 14:10:47 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
/* this function returns char ** with the RGB */
/* solo retorna NULL en caso de fallo de malloc */

static short int	*save_rgb(char **rgb_buf, bool *err)
{
	float		rgb[3];
	short int	*ret;
	short int	i;

	ret = ft_calloc(3, sizeof(short int));
	i = -1;
	if (!ret)
	{
		*err = true;
		return (NULL);
	}
	rgb[0] = ft_mod_atof(rgb_buf[0], err);
	rgb[1] = ft_mod_atof(rgb_buf[1], err);
	rgb[2] = ft_mod_atof(rgb_buf[2], err);
	while (++i < 3 && !*err)
		*err = (rgb[i] < 0.0 || rgb[i] > 255.0);
	ret[0] = rgb[0];
	ret[1] = rgb[1];
	ret[2] = rgb[2];
	return (ret);
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

short int	*object_rgb(t_llist *obj)
{
	if (obj->type == 3)
		return (((t_cylinder *)obj->content)->rgb);
	else if (obj->type == 4)
		return (((t_plane *)obj->content)->rgb);
	else if (obj->type == 5)
		return (((t_sphere *)obj->content)->rgb);
	return (0);
}

int	get_int_color(short int *rgb)
{
	int	i;

	i = -1;
	while (++i < 3)
		if (rgb[i] > 255)
			rgb[i] = 255;
	return ((rgb[0] << 24) + (rgb[1] << 16) + (rgb[2] << 8) + 255);
}
