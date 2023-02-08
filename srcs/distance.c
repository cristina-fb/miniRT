/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/02/08 18:53:12 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	distance_sphere(t_coord point, t_sphere sphere)
{
	return (vector_module(vector_sub(*sphere.center, point)) - sphere.radius);
}

double	distance_plane(t_coord point, t_plane plane)
{
	return (fabs(dot_product(*plane.normal, vector_sub(point, *plane.point))));
}

double	distance_cylinder(t_coord point, t_cylinder cylinder)
{
	double	da;
	double	dl;
	double	h;

	da = 0.0;
	h = dot_product(*cylinder.vector, vector_sub(point, *cylinder.ba));
	if (h > cylinder.height)
	{
		da = vector_module(vector_sub(*cylinder.bb, point));
		h = h - cylinder.height;
	}
	else
		da = vector_module(vector_sub(*cylinder.ba, point));
	dl = sqrt(pow(da, 2.0) - pow(h, 2.0));
	if ((dl < cylinder.radius) && (h < cylinder.height) && (h > 0))
		return (0);
	else if ((h >= 0) && (h <= cylinder.height))
		return (fabs(dl) - cylinder.radius);
	else if (dl <= cylinder.radius)
		return (fabs(h));
	else
		return (fabs(sqrt(pow(dl - cylinder.radius, 2.0) + pow(h, 2.0))));
	return (0.0);
}
