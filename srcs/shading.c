/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:57:56 by crisfern          #+#    #+#             */
/*   Updated: 2023/02/23 16:46:19 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coord	get_normal(t_llist *obj, t_coord *point)
{
	t_cylinder	*cy;
	int			d;
	if (obj->type == 3) //Hay que ver que pasa con las tapas
	{
		cy = (t_cylinder *)obj->content;
		d = dot_product(*cy->vector, v_sub(*point, *cy->ba));
		return (v_unit(v_sub(*point, v_add(*cy->ba, v_mul(*cy->vector, d)))));
	}
	else if (obj->type == 4)
		return (*((t_plane *)obj->content)->normal);
	else if (obj->type == 5)
		return (v_unit(v_sub(*point, \
		*((t_sphere *)obj->content)->center)));
	return ((t_coord){0, 0, 0});
}

double	pcolor(t_program *p, t_llist *obj, t_coord *point, t_coord *ray)
{
	double		light[3];
	t_coord		normal;
	t_coord		dir;
	double		ratio;
	short int	color[3];

	light[0] = p->ambient->ratio * p->ambient->rgb[0];
	light[1] = p->ambient->ratio * p->ambient->rgb[1];
	light[2] = p->ambient->ratio * p->ambient->rgb[2];
	if (obj)
	{
		dir = v_mul(*ray, -1);
		normal = get_normal(obj, point);
		ratio = dot_product(normal, dir);
		if (ratio < 0.0)
			ratio = 0.0;
		light[0] += ratio * p->light->rgb[0];
		light[1] += ratio * p->light->rgb[1];
		light[2] += ratio * p->light->rgb[2];
		color[0] = (light[0] / 255) * object_rgb(obj)[0];
		color[1] = (light[1] / 255) * object_rgb(obj)[1];
		color[2] = (light[2] / 255) * object_rgb(obj)[2];
	}
	return (get_int_color(color));
}
