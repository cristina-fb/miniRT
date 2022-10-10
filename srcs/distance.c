/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2022/10/10 18:18:12 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	distance_sphere(t_coord point, t_sphere sphere)
{
	return (vector_module(vector_sub(sphere.center, point)) - sphere.radius);
}

float	distance_plane(t_coord point, t_plane plane)
{
	return (fabs(dot_product(plane.normal, vector_sub(point, plane.point))));
}

float	distance_cylinder(t_coord point, t_cylinder cylinder)
{
	float	da;
	float	dl;
	float	h;

	da = 0.0;
	cylinder.bb = vector_add(cylinder.ba, vector_mul(cylinder.vector, cylinder.height));
	h = dot_product(cylinder.vector, vector_sub(point, cylinder.ba));
	if ((h >= 0) && (h <= cylinder.height))
	{
		da = vector_module(vector_sub(cylinder.ba, point));
		return (fabs(sqrt(pow(da, 2.0) - pow(h, 2.0)) - cylinder.radius));
	}
	else if (h < 0)
		da = vector_module(vector_sub(cylinder.ba, point));
	else if (h > cylinder.height)
	{
		da = vector_module(vector_sub(cylinder.bb, point));
		h = h - cylinder.height;
	}
	dl = sqrt(pow(da, 2.0) - pow(h, 2.0));
	printf("%.10f %.10f\n", dl, cylinder.radius);
	if (dl <= cylinder.radius)
		return (fabs(h));
	else
		return (fabs(sqrt(pow(dl - cylinder.radius, 2.0) + pow(h, 2.0))));
	return (0.0);
}
