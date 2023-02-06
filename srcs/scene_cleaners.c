/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_cleaners.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:01:53 by jalvarad          #+#    #+#             */
/*   Updated: 2023/02/06 17:53:24 by crisfern         ###   ########.fr       */
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

void	viewpane_cleaner(t_viewpane *viewpane)
{
	if (!viewpane)
		return ;
	free(viewpane->init);
	viewpane->init = NULL;
	free(viewpane->up);
	viewpane->up = NULL;
	free(viewpane->right);
	viewpane->right = NULL;
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
