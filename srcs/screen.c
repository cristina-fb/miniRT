/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:45:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/02/01 14:53:06 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
//TODO -> falta acabarla
void	init_point_vp(t_camera *camera, t_program *program)
{
	t_coord	vp_center;
	t_coord	up;
	t_coord	aux;

	up = (t_coord){0, 0, 1};
	camera->vp_width = 2 * tanf(camera->fov / 2);
	vp_center = vector_add(*(camera->center), *(camera->orientation));
	*(camera->vp_right) = vector_product(up, *(camera->orientation));
	*(camera->vp_up) = vector_product(*(camera->vp_right), *(camera->orientation));
	aux = vector_sub(vp_center, vector_mul());
	*(camera->vp_init) = vector_sub(aux, vector_mul(program-> ));
}
