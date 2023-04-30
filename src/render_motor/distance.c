/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/04/30 19:27:50 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

static double	get_dist(t_coord p, t_llist obj)
{
	if (obj.type == 3)
		return (distance_cylinder(p, \
		(t_cylinder *)obj.content));
	else if (obj.type == 4)
		return (distance_plane(p, (t_plane *)obj.content));
	return (distance_sphere(p, (t_sphere *)obj.content));
}

void	skipper(t_program *program, t_min_sdf_data *data, double dist, int i)
{
	if (!data->f_first)
		program->shapes[i].skip = false;
	else if (dist > program->shapes[i].last_dist)
		program->shapes[i].skip = true;
}

double	min_sdf_loop(t_coord p, t_program *program, t_min_sdf_data *data)
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
		if (!data->f_first || !program->shapes[i].skip)
		{
			dist = get_dist(p, program->shapes[i]);
			skipper(program, data, dist, i);
			program->shapes[i].last_dist = dist;
			if ((j == 0) || (fabs(dist) < fabs(min)))
			{
				min = dist;
				data->obj = program->shapes[i];
			}
			j++;
		}
	}
	data->f = !j;
	return (min);
}
