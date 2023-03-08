/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/03/08 18:57:52 by jalvarad         ###   ########.fr       */
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
  	t_coord  pa = v_sub(p, *cylinder->ba);
	double paba = dot_product(pa,*cylinder->ba_aux);
	double x = v_module(v_sub(v_mul(pa, cylinder->baba), v_mul(*cylinder->ba_aux, paba))) - cylinder->radius * cylinder->baba;
	double y = fabs(paba-(cylinder->baba*0.5))-(cylinder->baba*0.5);
	double x2 = x*x;
	double y2 = y*y*cylinder->baba;
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
			d += x2;
		}
		else
		{
			d += 0.0;
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
	return sign*sqrt(fabs(d))/cylinder->baba;
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
