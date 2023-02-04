/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_cleaners.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:01:53 by jalvarad          #+#    #+#             */
/*   Updated: 2023/02/04 13:44:39 by jalvarad         ###   ########.fr       */
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

void	view_plane_cleaner(t_view_plane *view_plane)
{
	if (!view_plane)
		return ;
	free(view_plane->vp_init);
	view_plane->vp_init = NULL;
	free(view_plane->vp_up);
	view_plane->vp_up = NULL;
	free(view_plane->vp_right);
	view_plane->vp_right = NULL;
}

void	camera_cleaner(t_camera *camera)
{
	if (!camera)
		return ;
	free(camera->center);
	camera->center = NULL;
	free(camera->orientation);
	camera->orientation = NULL;
	free(camera->view_plane);
	camera->view_plane = NULL;
}

void	light_cleaner(t_light *light)
{
	if (!light)
		return ;
	free(light->point);
	light->point = NULL;
}
