/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cris.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:45:59 by jalvarad          #+#    #+#             */
/*   Updated: 2023/02/08 14:25:56 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int main (void)
{
    t_coord	center = (t_coord){1.2, 2.3, 3.4};
	t_coord	orientation = (t_coord){0.71, 0.32, -0.63};
    t_camera cam = (t_camera){&center, &orientation, NULL, 60};
    init_vp(&cam, 1);
    pixels_array(1920, 1920, &cam);
    return (0);
}