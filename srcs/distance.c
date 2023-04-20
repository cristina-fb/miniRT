/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/04/20 12:22:22 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double distance_sphere(t_coord p, t_sphere *sphere)
{
    double dist;
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

double distance_cylinder(t_coord p, t_cylinder *cylinder)
{
    /*double 	x;
    double 	y;
	double	pa_squared;
	t_coord pa;
	
	pa.x = p.x - cylinder->ba->x;
	pa.y = p.y - cylinder->ba->y;
	pa.z = p.z - cylinder->ba->z;
	pa_squared = pow(pa.x, 2.0) + pow(pa.y, 2.0) + pow(pa.z, 2.0);
	y = ((pa.x * cylinder->ba_aux->x) + (pa.y * cylinder->ba_aux->y) + (pa.z * cylinder->ba_aux->z)) / cylinder->height;
    x = sqrt(pa_squared - (y * y)) - cylinder->radius;
    if ((y > -MIN_DIST) && (y < cylinder->height))
    {
        if (x < -MIN_DIST)
            return (0.0);
        return (x);
    }
    else if (x < -MIN_DIST)
    {
        if (y < -MIN_DIST)
            return (-y);
        return (y - cylinder->height);
    }
    else if (y > cylinder->height)
        y -= cylinder->height;
    return (sqrt(y * y + x * x));*/

	t_coord  ba;
	ba.x = cylinder->bb->x - cylinder->ba->x;
	ba.y = cylinder->bb->y - cylinder->ba->y;
	ba.z = cylinder->bb->z - cylinder->ba->z;
  	t_coord  pa;
	pa.x = p.x - cylinder->ba->x;
	pa.y = p.y - cylinder->ba->y;
	pa.z = p.z - cylinder->ba->z;
	double baba = pow(cylinder->height, 2.0);
	double paba = (pa.x * ba.x) + (pa.y * ba.y) + (pa.z * ba.z);
	double x = sqrt((pow((pa.x * baba) - (ba.x * paba), 2.0) + pow((pa.y * baba) - (ba.y * paba), 2.0) + pow((pa.z * baba) - (ba.z * paba), 2.0))) - cylinder->radius * baba;
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
		if (x>0.0)
			d = x2;
		if (y>0.0)
			d += y2;
	}
	if (d < 0.0)
		return (-1 * sqrt(fabs(d))/baba);
	return (sqrt(fabs(d))/baba);
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

static double get_dist(t_coord p, t_llist obj)
{
	if (obj.type == 3)
		return (distance_cylinder(p, \
		(t_cylinder *)obj.content));
	else if (obj.type == 4)
		return (distance_plane(p, (t_plane *)obj.content));
	return (distance_sphere(p, (t_sphere *)obj.content));
}

double	min_sdf_loop(t_coord p, t_program *program, t_llist *obj, int f_first, int *f)
{
	double	dist;
	double	min;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	min = 0;
	while (++i < program->n_geometries)
	{
		if (!f_first || !program->shapes[i].skip)
		{
			dist = get_dist(p, program->shapes[i]);
			if(!f_first)
				program->shapes[i].skip = false;
			else if (dist > program->shapes[i].last_dist)
				program->shapes[i].skip = true;
			program->shapes[i].last_dist = dist;
			if ((j == 0) || (fabs(dist) < fabs(min)))
			{
				min = dist;
				*obj = program->shapes[i];
			}
			j++;
		}
	}
	if (j == 0)
		*f = 1;
	return (min);
}
