/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:45:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/03/01 19:09:37 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//Falta ver que pasa con fov 180 //derecha es x
static void	fill_vp(t_camera *cam, t_coord *vp_center, t_coord *up)
{
	t_coord	aux;

	if ((cam->dir->x == up->x) && (cam->dir->y == up->y)
		&& (cam->dir->z == up->z))
	{
		*cam->vp->right = (t_coord){1, 0, 0};
		*cam->vp->up = (t_coord){0, 1, 0};
	}
	else
	{
		*cam->vp->right = v_unit((cross_product(*cam->dir, *up)));
		*cam->vp->up = v_unit(cross_product(*cam->vp->right, *cam->dir));
	}
	aux = v_sub(*vp_center, v_mul(*cam->vp->right, cam->vp->width / 2.0f));
	aux = v_sub(aux, v_mul(*cam->vp->up, cam->vp->height / 2.0f));
	aux = v_add(aux, v_mul(*cam->vp->right, cam->vp->pixel_width / 2.0f));
	*cam->vp->init = v_add(aux, v_mul(*cam->vp->up, cam->vp->pixel_height / 2.0f));
}

bool	init_vp(t_camera *cam)
{
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
	cam->vp->width = 2.00 * tanf((double)cam->fov / 2.00);
	cam->vp->height = (double)cam->vp->width / ((double)WIDTH / (double)HEIGHT);
	cam->vp->pixel_width = (double)cam->vp->width / (double)WIDTH;
    cam->vp->pixel_height = (double)cam->vp->height / (double)HEIGHT;
	printf("%f, %f, %f, %f\n",cam->vp->width,cam->vp->height, cam->vp->pixel_width, cam->vp->pixel_height);
	vp_center = v_add(*(cam->center), *(cam->dir));
	fill_vp(cam, &vp_center, &up);
	return (pixels_array(cam));
}

static void	fill_pixels_array(t_camera *cam, int i, int j, bool *err)
{
	t_coord	ray_center;
	t_coord	*ray;

	ray_center = v_add(*(cam->vp->init), \
	v_mul(*(cam->vp->up), (float)cam->vp->pixel_height * (float)(i + 0.5)));
	ray_center = v_add(ray_center, \
	v_mul(*(cam->vp->right), (float)cam->vp->pixel_width * (float)(j + 0.5)));
	ray = ft_calloc(1, sizeof(t_coord));
	if (!ray)
	{
		*err = true;
		return ;
	}
	*ray = v_unit(v_sub(ray_center, *(cam->center)));
	cam->vp->arr[HEIGHT - i - 1][j] = (t_pixel){ray, 0};
}

bool	pixels_array(t_camera *cam)
{
	int		i;
	int		j;
	int		indx;
	bool	err;

	err = false;
	i = -1;
	cam->vp->arr = (t_pixel**)malloc(HEIGHT * sizeof(t_pixel*));
	if (!cam->vp->arr)
		return (false);
	while (++i < HEIGHT)
	{
		j = -1;
		indx = HEIGHT - i - 1;
		cam->vp->arr[indx] = (t_pixel*)malloc(WIDTH * sizeof(t_pixel));
		if (cam->vp->arr[indx])
		{
			while (++j < WIDTH)
				fill_pixels_array(cam, i, j, &err);
		}
		else
		{
			err = true;
			exit(1);
		}
	}
	return (err == false);
}
