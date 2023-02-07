/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:45:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/02/07 16:13:29 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//Falta ver que pasa con fov 180
void	init_vp(t_camera *cam, double res)
{
	t_coord	aux;
	t_coord	vp_center;
	t_coord	up;

	up = (t_coord){0, 0, 1};
	cam->vp = ft_calloc(sizeof(t_viewpane), 1);
	if (!cam->vp)
		return ;
	cam->vp->right = ft_calloc(sizeof(t_coord), 1);
	cam->vp->up = ft_calloc(sizeof(t_coord), 1);
	cam->vp->init = ft_calloc(sizeof(t_coord), 1);
	if ((!cam->vp->init) || (!cam->vp->right) || (!cam->vp->up))
		return ;
	cam->vp->width = 2 * tanf((cam->fov / 2) * M_PI / 180);
	cam->vp->height = cam->vp->width * (1 / res);
	vp_center = vector_add(*(cam->center), *(cam->dir));
	*(cam->vp->right) = unit_vector((vector_product(*(cam->dir), up)));
	*(cam->vp->up) = unit_vector(vector_product(*(cam->vp->right), \
	*(cam->dir)));
	aux = vector_sub(vp_center, vector_mul(*(cam->vp->right), \
	cam->vp->width / 2));
	*(cam->vp->init) = vector_sub(aux, vector_mul(*(cam->vp->up), \
	cam->vp->height / 2));
}

void	pixels_array(int w, int h, t_camera *cam)
{
	int		i;
	int		j;
	t_coord	*ray;
	t_coord	ray_center;

	i = -1;
	cam->vp->arr = (t_pixel **)ft_calloc(sizeof(t_pixel[w]), h);
	if (!cam->vp->arr)
		return ;
	while (++i < h)
	{
		j = -1;
		cam->vp->arr[h - i - 1] = (t_pixel *)ft_calloc(sizeof(t_pixel), w);
		if (!cam->vp->arr[h - i - 1])
			return ;
		while (++j < w)
		{
			ray_center = vector_add(*(cam->vp->init), \
			vector_mul(*(cam->vp->up), cam->vp->height / h * (i + 0.5)));
			ray_center = vector_add(ray_center, \
			vector_mul(*(cam->vp->right), cam->vp->width / w * (j + 0.5)));
			ray = (t_coord *)ft_calloc(sizeof(t_coord), 1);
			*ray = unit_vector(vector_sub(ray_center, *(cam->center)));
			cam->vp->arr[h - i - 1][j] = (t_pixel){ray, 0};
		}
	}
}
