/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:45:34 by crisfern          #+#    #+#             */
/*   Updated: 2022/09/29 18:45:50 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float   distance_screen(t_camara *camara, int width)
{
    return((width / 2) / tanf(camara->fov / 2));
}

t_coord center_point_screen(t_camara *camara, int width)
{
    float   d;
    t_coord uvector;

    d = distance_screen(camara, width);
    uvector = unit_vector(camara->orientation);
    return(vector_add(camara->center, vector_mul(uvector, d)));
}
