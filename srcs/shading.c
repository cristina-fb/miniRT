/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:57:56 by crisfern          #+#    #+#             */
/*   Updated: 2023/02/22 15:32:24 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coord	get_normal(t_llist *obj, t_coord *point)
{
	if (obj->type == 5)
		return (unit_vector(vector_sub(*point, \
		*((t_sphere *)obj->content)->center)));
	return ((t_coord){0, 0, 0});
}

double	pcolor(t_program *p, t_llist *obj, t_coord *point, t_coord *ray)
{
	short int	light[3];
	t_coord		normal;
	t_coord		dir;
	double		ratio;

	light[0] = p->ambient->ratio * p->ambient->rgb[0];
	light[1] = p->ambient->ratio * p->ambient->rgb[1];
	light[2] = p->ambient->ratio * p->ambient->rgb[2];
	if (obj)
	{
		dir = vector_mul(*ray, -1);
		normal = get_normal(obj, point);
		ratio = dot_product(normal, dir);
		if (ratio < 0.0)
			ratio = 0.0;
		light[0] += ratio * object_rgb(obj)[0];
		light[1] += ratio * object_rgb(obj)[1];
		light[2] += ratio * object_rgb(obj)[2];
	}
	printf("\n%d %d %d ", light[0], light[1], light[2]);
	return (get_int_color(light));
}

