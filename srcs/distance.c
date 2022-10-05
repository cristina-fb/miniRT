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

float	distance_sphere(t_coord point, t_sphere sphere)
{
	return (vector_module(vector_sub(sphere.center, point)) - sphere.radius);
}

float	distance_plane(t_coord point, t_plane plane)
{
	return (abs(dot_product(plane.normal, vector_sub(point, plane.point))));
}

/*float distance_cylinder(t_coord *point, t_cylinder *cylinder)
{
    
}*/
