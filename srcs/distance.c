/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/02/13 13:06:09 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	distance_sphere(t_coord p, t_sphere *sphere)
{
	return (vector_module(vector_sub(*sphere->center, p)) - sphere->radius);
}

double	distance_plane(t_coord p, t_plane *plane)
{
	return (fabs(dot_product(*plane->normal, vector_sub(p, *plane->point))));
}

double	distance_cylinder(t_coord p, t_cylinder *cylinder)
{
	double	da;
	double	dl;
	double	h;

	da = 0.0;
	h = dot_product(*cylinder->vector, vector_sub(p, *cylinder->ba));
	if (h > cylinder->height)
	{
		da = vector_module(vector_sub(*cylinder->bb, p));
		h = h - cylinder->height;
	}
	else
		da = vector_module(vector_sub(*cylinder->ba, p));
	dl = sqrt(pow(da, 2.0) - pow(h, 2.0));
	if ((dl < cylinder->radius) && (h < cylinder->height) && (h > 0))
		return (0);
	else if ((h >= 0) && (h <= cylinder->height))
		return (fabs(dl) - cylinder->radius);
	else if (dl <= cylinder->radius)
		return (fabs(h));
	else
		return (fabs(sqrt(pow(dl - cylinder->radius, 2.0) + pow(h, 2.0))));
	return (0.0);
}

double	min_distance(t_coord p, t_program *program)
{
	double	min;
	double	dist;
	size_t	i;

	i = -1;
	while (++i < program->n_geometries)
	{
		if (program->shapes[i].type == 3)
			dist = distance_cylinder(p, \
			(t_cylinder *)program->shapes[i].content);
		else if (program->shapes[i].type == 4)
			dist = distance_plane(p, (t_plane *)program->shapes[i].content);
		else if (program->shapes[i].type == 5)
			dist = distance_sphere(p, (t_sphere *)program->shapes[i].content);
		if ((i == 0) || ((dist > 0) && (dist < min)))
		{
			min = dist;
		}
	}
	/*if (min < MIN_DIST)
		//colision*/
	printf("%f\n", min);
	return (min);
}
