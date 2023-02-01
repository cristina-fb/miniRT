/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:45:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/02/01 18:15:52 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_point_vp(t_camera *cam, t_program *program)
{
	t_coord	vp_center;
	t_coord	up;
	t_coord	aux;

	up = (t_coord){0, 0, 1};
	cam->vp_width = 2 * tanf(cam->fov / 2);
	vp_center = vector_add(*(cam->center), *(cam->orientation));
	*(cam->vp_right) = vector_product(up, *(cam->orientation));
	*(cam->vp_up) = vector_product(*(cam->vp_right), *(cam->orientation));
	aux = vector_sub(vp_center, vector_mul(*(cam->vp_right), cam->vp_width / 2));
	*(cam->vp_init) = vector_sub(aux, vector_mul(aux, height/2)); //height sale del ratio de la pantalla
}

void	pixels_array(int width, int height, t_camera *cam)
{
	int		i;
	int		j;
	t_coord	*ray;
	t_coord	ray_center;
	t_pixel	**pixels;

	i = 0;
	pixels = (t_pixel **)malloc(sizeof(t_pixel) * width * height);
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			ray_center = cam->vp_init + +; //Coger el centro de cada pixel
			ray = (t_coord *)malloc(sizeof(t_coord));
			*ray = vector_sub(ray_center, *(cam->center));
			pixels[i][height - j - 1] = (t_pixel){ray, 0};
			j++;
		}
		i++;
	}
}
