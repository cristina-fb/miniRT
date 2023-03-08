/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:57:56 by crisfern          #+#    #+#             */
/*   Updated: 2023/03/08 18:40:11 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coord	get_normal(t_program *p, t_coord *point)
{
	t_coord	norm;
	t_coord	aux1;
	t_coord	aux2;

	aux1 = *point;
	aux2 = *point;
	aux1.x += 0.001;
	aux2.x -= 0.001;
	norm.x = min_sdf(aux1, p) - min_sdf(aux2, p);
	aux1 = *point;
	aux2 = *point;
	aux1.y += 0.001;
	aux2.y -= 0.001;
	norm.y = min_sdf(aux1, p) - min_sdf(aux2, p);
	aux1 = *point;
	aux2 = *point;
	aux1.z += 0.001;
	aux2.z -= 0.001;
	norm.z = min_sdf(aux1, p) - min_sdf(aux2, p);
	return (v_unit(norm));
}

double	pcolor(t_program *p, t_llist *obj, t_coord *point)
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
		dir = v_unit(v_sub(*p->light->point, *point));
		normal = get_normal(p, point);
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
