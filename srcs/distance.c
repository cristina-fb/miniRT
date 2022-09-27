/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2022/09/27 16:23:52 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	distance_sphere(t_coord *point, t_sphere *sphere)
{
	return (vector_module(point, sphere->center) - sphere->radius);
}

float	distance_plane(t_coord *point, t_plane *plane)
{
	t_coord	*origin;

	origin->x = 0;
	origin->y = 0;
	origin->z = 0;
	return (abs(dot_product(plane->normal, vector_sub(point, plane->point))) / (vector_mod(plane->normal, origin)));
}

/*float distance_cylinder(t_coord *point, t_cylinder *cylinder)
{
    
}*/
