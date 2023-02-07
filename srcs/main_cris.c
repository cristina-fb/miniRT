/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cris.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:45:59 by jalvarad          #+#    #+#             */
/*   Updated: 2023/02/07 15:07:24 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int main (void)
{
    t_coord	center = (t_coord){0, 1, 0};
	t_coord	orientation = (t_coord){0.84, -0.2, 0.5};
    t_camera cam = (t_camera){&center, &orientation, NULL, 120};
    init_vp(&cam, 1);
    pixels_array(10, 10, &cam);
    return (0);
}
