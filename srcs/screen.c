/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:45:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/02/06 18:03:11 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_vp(t_camera *cam, double res)
{
	t_coord	vp_center;
	t_coord	up;
	t_coord	aux;

	up = (t_coord){0, 0, 1};
	cam->vp->right = ft_calloc(sizeof(t_coord), 1);
	cam->vp->up = ft_calloc(sizeof(t_coord), 1);
	cam->vp->init = ft_calloc(sizeof(t_coord), 1);
	if ((!cam->vp->init) || (!cam->vp->right) || (!cam->vp->up))
		return ;
	cam->vp->width = 2 * tanf((cam->fov / 2) * M_PI / 180);
	cam->vp->height = cam->vp->width * (1 / res);
	vp_center = vector_add(*(cam->center), *(cam->dir));
	*(cam->vp->right) = (vector_product(up, *(cam->dir)));
	*(cam->vp->up) = unit_vector(vector_product(*(cam->vp->right), \
	*(cam->dir)));
	aux = vector_sub(vp_center, vector_mul(*(cam->vp->right), \
	cam->vp->width / 2));
	*(cam->vp->init) = vector_sub(aux, vector_mul(*(cam->vp->up), \
	cam->vp->height / 2));
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
			ray_center = vector_add(*(cam->vp->init), \
			vector_mul(*(cam->vp->up), cam->vp->height / height * (i + 0.5)));
			ray_center = vector_add(ray_center, \
			vector_mul(*(cam->vp->right), cam->vp->width / width * (j + 0.5)));
			ray = (t_coord *)malloc(sizeof(t_coord));
			*ray = unit_vector(vector_sub(ray_center, *(cam->center)));
			pixels[height - i - 1][j] = (t_pixel){ray, 0};
			j++;
		}
		i++;
	}
}
