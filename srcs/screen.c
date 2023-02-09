/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:45:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/02/09 14:44:12 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//Falta ver que pasa con fov 180
bool	init_vp(t_camera *cam)
{
	t_coord	aux;
	t_coord	vp_center;
	t_coord	up;

	up = (t_coord){0, 0, 1};
	cam->vp = ft_calloc(1, sizeof(t_viewpane));
	if (!cam->vp)
		return (false);
	cam->vp->right = ft_calloc(1, sizeof(t_coord));
	cam->vp->up = ft_calloc(1, sizeof(t_coord));
	cam->vp->init = ft_calloc(1, sizeof(t_coord));
	if ((!cam->vp->init) || (!cam->vp->right) || (!cam->vp->up))
		return (false);
	cam->vp->width = 2 * tanf(cam->fov / 2);
	cam->vp->height = cam->vp->width * (1 / (WIDTH / HEIGHT));
	vp_center = vector_add(*(cam->center), *(cam->dir));
	*(cam->vp->right) = unit_vector((vector_product(*(cam->dir), up)));
	*(cam->vp->up) = unit_vector(vector_product(*(cam->vp->right), \
	*(cam->dir)));
	aux = vector_sub(vp_center, vector_mul(*(cam->vp->right), \
	cam->vp->width / 2));
	*(cam->vp->init) = vector_sub(aux, vector_mul(*(cam->vp->up), \
	cam->vp->height / 2));
	return (pixels_array(cam));
}

static void	fill_pixels_array(t_camera *cam, int i, int j, bool *err)
{
	t_coord	ray_center;
	t_coord	*ray;

	ray_center = vector_add(*(cam->vp->init), \
	vector_mul(*(cam->vp->up), cam->vp->height / WIDTH * (i + 0.5)));
	ray_center = vector_add(ray_center, \
	vector_mul(*(cam->vp->right), cam->vp->width / WIDTH * (j + 0.5)));
	ray = ft_calloc(1, sizeof(t_coord));
	if (!ray)
	{
		*err = true;
		return ;
	}
	*ray = unit_vector(vector_sub(ray_center, *(cam->center)));
	cam->vp->arr[HEIGHT - i - 1][j] = (t_pixel){ray, 0};
}

bool	pixels_array(t_camera *cam)
{
	int		i;
	int		j;
	bool	err;

	err = false;
	i = -1;
	cam->vp->arr = ft_calloc(HEIGHT, sizeof(t_pixel[WIDTH]));
	if (!cam->vp->arr)
		return (false);
	while (++i < HEIGHT)
	{
		j = -1;
		cam->vp->arr[HEIGHT - i - 1] = ft_calloc(WIDTH, sizeof(t_pixel));
		if (cam->vp->arr[HEIGHT - i - 1])
			while (++j < WIDTH)
				fill_pixels_array(cam, i, j, &err);
		else
			err = true;
	}
	return (err);
}
