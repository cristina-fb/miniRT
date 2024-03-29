/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/05/05 18:45:56 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	distance_torus(t_coord p, t_torus *torus)
{
	double	h;
	double	pc;
	double	x;

	h = (torus->center->x - p.x) * torus->orientation->x;
	h += (torus->center->y - p.y) * torus->orientation->y;
	h += (torus->center->z - p.z) * torus->orientation->z;
	if (torus->distortion)
	{
		if (h < 0)
			p.z += (h / 3) * sin(0.5 / h * p.z);
		p.x += sin(0.5 * p.x) * cos(0.5 * p.y);
	}
	h = fabs(h);
	pc = v_module(v_sub(p, *torus->center));
	x = sqrt(pow(pc, 2.0) - pow(h, 2.0)) - torus->t_x;
	return (sqrt(pow(h, 2.0) + pow(x, 2.0)) - torus->t_y);
}

double	distance_sphere(t_coord p, t_sphere *sphere)
{
	double	dist;

	dist = pow(p.x - sphere->center->x, 2.0);
	dist += pow(p.y - sphere->center->y, 2.0);
	dist += pow(p.z - sphere->center->z, 2.0);
	return (sqrt(dist) - sphere->radius);
}

double	distance_plane(t_coord p, t_plane *plane)
{
	double	dist;

	dist = (plane->point->x - p.x) * plane->normal->x;
	dist += (plane->point->y - p.y) * plane->normal->y;
	dist += (plane->point->z - p.z) * plane->normal->z;
	return (fabs(dist));
}

double	distance_cylinder(t_coord p, t_cylinder *cy)
{
	t_coord	pa;
	double	paba;
	double	x;
	double	y;

	pa.x = p.x - cy->base->x;
	pa.y = p.y - cy->base->y;
	pa.z = p.z - cy->base->z;
	paba = (pa.x * cy->ba->x) + (pa.y * cy->ba->y) + (pa.z * cy->ba->z);
	x = sqrt((pow((pa.x * cy->baba) - (cy->ba->x * paba), 2.0) + \
	pow((pa.y * cy->baba) - (cy->ba->y * paba), 2.0) + pow((pa.z * cy->baba) - \
	(cy->ba->z * paba), 2.0))) - cy->radius * cy->baba;
	y = fabs(paba - (cy->baba * 0.5)) - (cy->baba * 0.5);
	if ((x < 0.0) && (y < 0.0))
	{
		if ((x * x) > (y * y * cy->baba))
			return (-1 * sqrt(fabs(-y * y * cy->baba)) / cy->baba);
		else
			return (-1 * sqrt(fabs(-x * x)) / cy->baba);
	}
	if ((x > 0.0) && (y > 0.0))
		return (sqrt(fabs(x * x + y * y * cy->baba)) / cy->baba);
	if (x > 0.0)
		return (sqrt(fabs(x * x)) / cy->baba);
	return (sqrt(fabs(y * y * cy->baba)) / cy->baba);
}
