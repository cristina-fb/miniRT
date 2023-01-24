/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:45:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/01/24 19:29:05 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
//TODO -> falta acabarla
void	init_point_vp(t_camera *camera, t_program *program)
{
	t_coord	vp_center;
	t_coord	up_vector;
	t_coord	aux;

	up_vector.x = 0;
	up_vector.y = 0;
	up_vector.z = 1;
	camera->vp_width = 2 * tanf(camera->fov / 2);
	vp_center = vector_add(*(camera->center), *(camera->orientation));
	*(camera->vp_right) = vector_product(up_vector, *(camera->orientation));
	*(camera->vp_up) = vector_product(*(camera->vp_right), *(camera->orientation));
	aux = vector_sub(vp_center, vector_mul());
	*(camera->vp_init) = vector_sub(aux, vector_mul(program-> ));
}
