/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cris.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:45:59 by jalvarad          #+#    #+#             */
/*   Updated: 2022/10/10 18:17:26 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int main (void)
{
    t_coord a;
    a.x = 0.0;
    a.y = 0.9999999999999;
    a.z = 3.0;
    t_sphere b;
    b.center.x = 1.0;
    b.center.y = 1.0;
    b.center.z = 1.0;
    b.radius = 1.0;
    t_plane c;
    c.normal.x = 0.577350;
    c.normal.y = -0.577350;
    c.normal.z = 0.577350;
    c.point.x = 3.0;
    c.point.y = 1.0;
    c.point.z = 2.0;
    t_cylinder d;
    d.ba.x = 0.0;
    d.ba.y = 0.0;
    d.ba.z = 0.0;
    d.height = 2.0;
    d.vector.x = 0.0;
    d.vector.y = 0.0;
    d.vector.z = 1.0;
    d.radius = 1.0;
    printf("%f\n", distance_cylinder(a, d));
    return (0);
}
