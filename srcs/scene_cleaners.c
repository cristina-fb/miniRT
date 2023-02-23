/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_cleaners.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:01:53 by jalvarad          #+#    #+#             */
/*   Updated: 2023/02/09 14:38:03 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ambient_light_cleaner(t_ambient *ambient)
{
	if (!ambient)
		return ;
	free(ambient->rgb);
	ambient->rgb = NULL;
}

void	viewpane_arr_cleaner(t_viewpane *viewpane)
{
	int	i;
	int	j;

	i = -1;
	while (++i < HEIGHT)
	{
		if (viewpane->arr[i])
		{
			j = -1;
			while (++j < WIDTH)
			{
				if (viewpane->arr[i][j].ray)
				{
					free(viewpane->arr[i][j].ray);
					viewpane->arr[i][j].ray = NULL;
				}
			}
			free(viewpane->arr[i]);
			viewpane->arr[i] = NULL;
		}
	}
}

void	viewpane_cleaner(t_viewpane *viewpane)
{
	if (!viewpane)
		return ;
	if (viewpane->init)
	{
		free(viewpane->init);
		viewpane->init = NULL;
	}
	if (viewpane->up)
	{
		free(viewpane->up);
		viewpane->up = NULL;
	}
	if (viewpane->right)
	{
		free(viewpane->right);
		viewpane->right = NULL;
	}
	if (viewpane->arr)
	{
		viewpane_arr_cleaner(viewpane);
		free(viewpane->arr);
		viewpane->arr = NULL;
	}
}

void	camera_cleaner(t_camera *camera)
{
	if (!camera)
		return ;
	free(camera->center);
	camera->center = NULL;
	free(camera->dir);
	camera->dir = NULL;
	free(camera->vp);
	camera->vp = NULL;
}

void	light_cleaner(t_light *light)
{
	if (!light)
		return ;
	free(light->point);
	light->point = NULL;
}
