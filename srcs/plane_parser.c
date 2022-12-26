/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:26:45 by jalvarad          #+#    #+#             */
/*   Updated: 2022/12/26 17:46:02 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	get_plane_data(t_plane *plane, t_program *program)
{
	bool	err;

	err = false;
	plane->point = get_coords(program->attr_buf[1]);
	plane->normal = orientation_vector(program->attr_buf[2]);
	plane->rgb = get_rgb(program->attr_buf[3], &err);
	if (!plane->point || !plane->normal || err || !plane->rgb)
	{
		plane_cleaner(plane);
		return (false);
	}
	return (true);
}

static bool	plane_basic_parse(t_program *program)
{
	return (ft_word_count(program->attr_buf[1], ',') != 3 || \
		ft_word_count(program->attr_buf[2], ',') != 3 || \
		ft_word_count(program->attr_buf[3], ',') != 3);
}

bool	parse_plane(t_program *program)
{
	t_plane	*plane;
	t_list	*new;

	if (plane_basic_parse(program))
		return (false);
	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (false);
	*plane = (t_plane){NULL, NULL, NULL};
	if (!get_plane_data(plane, program))
		return (false);
	new = ft_mod_lstnew(PLANE, plane);
	if (!new)
		return (false);
	ft_lstadd_back(&program->geometries, new);
	return (true);
}
