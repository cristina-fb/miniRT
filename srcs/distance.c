/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/03/10 15:41:13 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	distance_sphere(t_coord p, t_sphere *sphere)
{
	return (v_module(v_sub(*sphere->center, p)) - sphere->radius);
}

double	distance_plane(t_coord p, t_plane *plane)
{
	return (fabs(dot_product(*plane->normal, v_sub(p, *plane->point))));
}

double	distance_cylinder(t_coord p, t_cylinder *cylinder)
{
	/*t_coord  ba = v_sub(*cylinder->bb, *cylinder->ba); //h
  	t_coord  pa = v_sub(p, *cylinder->ba); //pa
  	double baba = dot_product(ba,ba); //h^2
	double paba = dot_product(pa,ba); //h' * h
	double x = v_module(v_sub(v_mul(pa, baba), v_mul(ba, paba))) - cylinder->radius * baba;
	double y = fabs(paba-(baba*0.5))-(baba*0.5);
	double x2 = x*x;
	double y2 = y*y*baba;
	double d = 0.0;

	double aux;
	if (x < y)
		aux = y;
	else
		aux = x;
	if (aux<0.0)
	{
		if (x2 > y2)
			d = -y2;
		else
			d = -x2;
	}
	else
	{
		if ((x>0.0))
		{
			d = x2;
		}
		else
		{
			d = 0.0;
		}
		if ((y>0.0))
		{
			d += y2;
		}
		else
		{
			d += 0.0;
		}
	}
	int sign = 1;
	if (d < 0.0)
		sign = -1;
	return sign*sqrt(fabs(d))/baba;*/

	double x;
	double y;

	t_coord  ba = v_sub(*cylinder->bb, *cylinder->ba); //h
  	t_coord  pa = v_sub(p, *cylinder->ba); //pa

	y = dot_product(pa, ba) / cylinder->height;
	x = sqrt(pow(v_module(pa), 2.0) - (y * y)) - cylinder->radius;

	if ((y >= 0.0) && (y <= cylinder->height))
	{
		if (x <= 0.0)
			return (0.0);
		else
			return (x);
	}
	else if (x <= 0.0)
	{
		if (y <= 0.0)
			return (-y);
		else
			return (y - cylinder->height);
	}
	else
	{
		if (y >= cylinder->height)
			y -= cylinder->height;
		return (sqrt((y * y) + (x * x)));
	}
}

t_llist	*min_distance(t_coord p, t_program *program, double *min)
{
	double	dist;
	t_llist	*obj;
	size_t	i;

	i = -1;
	*min = 0;
	obj = NULL;
	while (++i < program->n_geometries)
	{
		if (program->shapes[i].type == 3)
			dist = distance_cylinder(p, \
			(t_cylinder *)program->shapes[i].content);
		else if (program->shapes[i].type == 4)
			dist = distance_plane(p, (t_plane *)program->shapes[i].content);
		else if (program->shapes[i].type == 5)
			dist = distance_sphere(p, (t_sphere *)program->shapes[i].content);
		if ((i == 0) || ((dist > 0) && (dist < *min)))
		{
			*min = dist;
			obj = &program->shapes[i];
		}
	}
	if (*min < MIN_DIST)
		return (obj);
	return (0);
}

double	min_sdf(t_coord p, t_program *program)
{
	double	dist;
	double	min;
	size_t	i;

	i = -1;
	min = 0;
	while (++i < program->n_geometries)
	{
		if (program->shapes[i].type == 3)
			dist = distance_cylinder(p, \
			(t_cylinder *)program->shapes[i].content);
		else if (program->shapes[i].type == 4)
			dist = distance_plane(p, (t_plane *)program->shapes[i].content);
		else if (program->shapes[i].type == 5)
			dist = distance_sphere(p, (t_sphere *)program->shapes[i].content);
		if ((i == 0) || (fabs(dist) < fabs(min)))
			min = dist;
	}
	return (min);
}
