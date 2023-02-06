/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:45:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/02/03 14:50:47 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_point_vp(t_camera *cam)
{
	t_coord	vp_center;
	t_coord	up;
	t_coord	aux;

	up = (t_coord){0, 0, 1};
	cam->vp_right = ft_calloc(sizeof(t_coord), 1);
	cam->vp_up = ft_calloc(sizeof(t_coord), 1);
	cam->vp_init = ft_calloc(sizeof(t_coord), 1);
	cam->vp_width = 2 * tanf((cam->fov / 2) * M_PI / 180);
	printf("%f\n", cam->vp_width);
	//cam->vp_height = cam->vp_width * res; //necesitamos el ratio de resolucion de la pantalla
	vp_center = vector_add(*(cam->center), *(cam->orientation));
	*(cam->vp_right) = (vector_product(up, *(cam->orientation))); 
	*(cam->vp_up) = unit_vector(vector_product(*(cam->vp_right), *(cam->orientation)));
	aux = vector_sub(vp_center, vector_mul(*(cam->vp_right), cam->vp_width / 2));
	//*(cam->vp_init) = vector_sub(aux, vector_mul(aux, cam->vp_height / 2)); //height sale del ratio de la pantalla
	printf("%f %f %f\n", cam->vp_right->x, cam->vp_right->y, cam->vp_right->z);
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
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			ray_center = vector_add(*(cam->vp_init), \
			vector_mul(*(cam->vp_up), cam->vp_height / height * (i + 0.5)));
			ray_center = vector_add(ray_center, \
			vector_mul(*(cam->vp_right), cam->vp_width / width * (j + 0.5)));
			ray = (t_coord *)malloc(sizeof(t_coord));
			*ray = unit_vector(vector_sub(ray_center, *(cam->center)));
			pixels[height - i - 1][j] = (t_pixel){ray, 0};
			j++;
		}
		i++;
	}
}
