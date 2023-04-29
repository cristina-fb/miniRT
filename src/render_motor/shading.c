/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 12:57:56 by crisfern          #+#    #+#             */
/*   Updated: 2023/04/29 15:14:26 by jalvarad         ###   ########.fr       */
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

bool	is_in_shadow(t_program *p, t_coord *point, t_coord *light_dir)
{
	double	t;
	double	min_dist;
	double	max_distance;
	int		steps;
	t_coord	ray_point;

	steps = 0;
	t = 0.001;
	max_distance = v_module(v_sub(*point, *p->light->point));
	while ((t < max_distance) && (steps++ < MAX_STEPS))
	{
		ray_point = v_add(*point, v_mul(*light_dir, t));
		min_dist = min_sdf(ray_point, p);
		if (min_dist < 0.0001)
			return (true);
		t += min_dist;
	}
	return (false);
}

static void	init_light(t_program *p, double light[3])
{
	light[0] = p->ambient->ratio * p->ambient->rgb[0];
	light[1] = p->ambient->ratio * p->ambient->rgb[1];
	light[2] = p->ambient->ratio * p->ambient->rgb[2];
}

double	pcolor(t_program *p, t_coord *point, t_llist *obj)
{
	double		light[3];
	t_coord		normal;
	t_coord		dir;
	double		ratio;
	short int	color[3];

	init_light(p, light);
	if (obj)
	{
		dir = v_unit(v_sub(*p->light->point, *point));
		normal = get_normal(p, point);
		ratio = dot_product(normal, dir);
		if (ratio < 0.0)
			ratio = 0.0;
		if (!is_in_shadow(p, point, &dir))
		{
			light[0] += ratio * p->light->rgb[0];
			light[1] += ratio * p->light->rgb[1];
			light[2] += ratio * p->light->rgb[2];
		}
		color[0] = (light[0] / 255) * object_rgb(obj)[0];
		color[1] = (light[1] / 255) * object_rgb(obj)[1];
		color[2] = (light[2] / 255) * object_rgb(obj)[2];
	}
	return (get_int_color(color));
}
