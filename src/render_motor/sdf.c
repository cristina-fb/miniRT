/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:59:51 by jalvarad          #+#    #+#             */
/*   Updated: 2023/05/02 17:24:50 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
		else if (program->shapes[i].type == 6)
			dist = sdTorus(p, (t_torus *)program->shapes[i].content);
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
	else if (obj.type == 5)
		return (distance_sphere(p, (t_sphere *)obj.content));
	return (sdTorus(p, (t_torus *)obj.content));
}

static void	skipper(t_program *prog, t_min_sdf_data *data, double dist, int i)
{
	if (!data->f_first)
		prog->shapes[i].skip = false;
	else if (dist > prog->shapes[i].last_dist)
		prog->shapes[i].skip = true;
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