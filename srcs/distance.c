/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2022/09/21 17:21:13 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float distance_sphere(t_coord *point, t_sphere *sphere)
{
    return (vector_module(point, sphere->center) - sphere->radius);
}

/*float distance_plane(t_coord *point, t_plane *plane)
{
    
}

float distance_cylinder(t_coord *point, t_cylinder *cylinder)
{
    
}*/