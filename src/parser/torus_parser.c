/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:51:13 by jalvarad          #+#    #+#             */
/*   Updated: 2023/05/04 18:18:55 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	get_torus_data(t_torus *torus, t_program *program)
{
	bool	err;

	err = false;
	torus->t_x = ft_mod_atof(program->attr_buf[1], &err);
	torus->t_y = ft_mod_atof(program->attr_buf[2], &err);
	torus->distortion = ft_mod_atof(program->attr_buf[3], &err);
	torus->rgb = get_rgb(program->attr_buf[4], &err);
	torus->center = get_coords(program->attr_buf[5]);
	torus->orientation = orientation_vector(program->attr_buf[6]);
	if (err || !torus->rgb || torus->t_x < 0.0 || torus->t_y < 0.0)
	{
		torus_cleaner(torus);
		return (false);
	}
	return (true);
}

static bool	torus_basic_parse(t_program *program)
{
	if (!str_is_float(program->attr_buf[1]) || \
		!str_is_float(program->attr_buf[2]) || \
		ft_word_count(program->attr_buf[4], ',') != 3)
		return (true);
	if (ft_word_count(program->attr_buf[5], ',') != 3 || \
		ft_word_count(program->attr_buf[6], ',') != 3)
		return (true);
	return (false);
}

bool	parse_torus(t_program *program)
{
	t_torus	*torus;
	t_list	*new;

	if (torus_basic_parse(program))
		return (false);
	torus = ft_calloc(1, sizeof(t_torus));
	if (!torus)
		return (false);
	*torus = (t_torus){0.00, 0.00, 0, NULL, NULL, NULL};
	if (!get_torus_data(torus, program))
		return (false);
	new = ft_mod_lstnew(TORUS, torus);
	if (!new)
		return (false);
	ft_lstadd_back(&program->geometries, new);
	return (true);
}
