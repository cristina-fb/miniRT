/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cris.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:45:59 by jalvarad          #+#    #+#             */
/*   Updated: 2022/10/11 18:55:32 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int main (void)
{
    t_coord a;
    a.x = -1.92;
    a.y = 5.15;
    a.z = 4.83;
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
    d.ba.x = -1.42;
    d.ba.y = 9.29;
    d.ba.z = 4.83;
    d.height = 11.36;
    d.vector.x = -0.8468;
    d.vector.y = -0.4216;
    d.vector.z = -0.3239;
    d.radius = 2.22;
    printf("%f\n", distance_cylinder(a, d));
    return (0);
}
