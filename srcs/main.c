/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:45:59 by jalvarad          #+#    #+#             */
/*   Updated: 2022/09/23 16:52:10 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int main (void)
{
    t_coord a;
    a.x = 0.0;
    a.y = 0.0;
    a.z = 0.0;
    t_sphere b;
    b.center->x = 1.0;
    b.center->y = 1.0;
    b.center->z = 1.0;
    b.radius = 1.0;
    printf("Resultado: %f\n", distance_sphere(&a, &b));
    return (0);
}