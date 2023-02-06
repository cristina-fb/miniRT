/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cris.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:45:59 by jalvarad          #+#    #+#             */
/*   Updated: 2023/02/02 15:14:06 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int main (void)
{
    t_coord	center = (t_coord){0, 0, 0};
	t_coord	orientation = (t_coord){1, 0, 0};
    t_camera cam = (t_camera){&center, &orientation,NULL, NULL, NULL, 120, 0, 0};
    init_point_vp(&cam);
    return (0);
}
