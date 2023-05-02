#include "miniRT.h"

static bool	get_torus_data(t_torus *torus, t_program *program)
{
	bool	err;

	err = false;
	torus->t_x = ft_mod_atof(program->attr_buf[1], &err);
	torus->t_y = ft_mod_atof(program->attr_buf[2], &err);
	torus->rgb = get_rgb(program->attr_buf[3], &err);
	torus->center = get_coords(program->attr_buf[4]);
	torus->orientation = get_coords(program->attr_buf[5]);
	if (err || !torus->rgb || torus->t_x < 0.0 || torus->t_y < 0.0)
	{
		////sphere_cleaner(sphere);   faalt hacer función de liberar
		return (false);
	}
	return (true);
}

static bool	torus_basic_parse(t_program *program)
{
	return (!str_is_float(program->attr_buf[1]) || \
		!str_is_float(program->attr_buf[2]) || \
		ft_word_count(program->attr_buf[3], ',') != 3 || ft_word_count(program->attr_buf[4], ',') != 3 || ft_word_count(program->attr_buf[5], ',') != 3);
}

bool	parse_torus(t_program *program)
{
	t_torus	*torus;
	t_list		*new;

	if (torus_basic_parse(program))
		return (false);
	torus = ft_calloc(1, sizeof(t_torus));
	if (!torus)
		return (false);
	*torus = (t_torus){0.00, 0.00, NULL, NULL, NULL};
	if (!get_torus_data(torus, program))
		return (false);
	new = ft_mod_lstnew(TORUS, torus);
	if (!new)
		return (false);
	ft_lstadd_back(&program->geometries, new);
	return (true);
}
