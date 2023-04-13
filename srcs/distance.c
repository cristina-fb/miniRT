/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/04/13 18:28:24 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double distance_sphere(t_coord p, t_sphere *sphere)
{
    double dist = pow(p.x - sphere->center->x, 2.0);
    dist += pow(p.y - sphere->center->y, 2.0);
    dist += pow(p.z - sphere->center->z, 2.0);
    return (sqrt(dist) - sphere->radius);
}

double	distance_plane(t_coord p, t_plane *plane)
{
	return (fabs(dot_product(*plane->normal, v_sub(p, *plane->point))));
}

double distance_cylinder(t_coord p, t_cylinder *cylinder)
{
    double x;
    double y;

    t_coord pa = v_sub(p, *cylinder->ba);

    y = dot_product(pa, *cylinder->ba_aux) / cylinder->height;
    double y_squared = y * y;
    double pa_squared = dot_product(pa, pa);
    x = sqrt(pa_squared - y_squared) - cylinder->radius;

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

    return (sqrt(y * y + x * x));
}

t_llist	*min_distance(t_coord p, t_program *program, double *min)
{
	double	dist;
	t_llist	*obj;
	size_t	i;

	i = -1;
	*min = 0.0;
	obj = NULL;
	//(void)rd;
	while (++i < program->n_geometries)
	{
		if (program->shapes[i].type == 3)
			dist = distance_cylinder(p, \
			(t_cylinder *)program->shapes[i].content);
		else if (program->shapes[i].type == 4)
			dist = distance_plane(p, (t_plane *)program->shapes[i].content);
		else if (program->shapes[i].type == 5)
			dist = distance_sphere(p, (t_sphere *)program->shapes[i].content);
		if ((i == 0) || ((dist > 0.0) && (dist < *min))) // en algún momento dist será menor a 0?
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
