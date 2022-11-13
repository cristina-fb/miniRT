/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:25:32 by jalvarad          #+#    #+#             */
/*   Updated: 2022/11/13 13:11:01 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool file_format(char *file_name)
{
	short int start_sufix;
	short int str_len;

	str_len = ft_strlen(file_name);
	start_sufix = str_len - 3;
	if (start_sufix >= 0 && str_len > 3)
		return (!ft_strncmp(file_name + start_sufix, ".rt", 3));
	return (false);
}
/* this function returns char ** with the RGB */
/* solo retorna NULL en caso de fallo de malloc */

short int *save_rgb(char **rgb_buf, bool *err)
{
	short int *rgb;
	short int i;

	rgb = ft_calloc(3, sizeof(short int));
	i = -1;
	if (!rgb)
	{
		*err = true;
		return (NULL);
	}
	rgb[0] = ft_mod_atof(rgb_buf[0], err);
	rgb[1] = ft_mod_atof(rgb_buf[1], err);
	rgb[2] = ft_mod_atof(rgb_buf[2], err);
	while (++i < 3 && !*err)
		*err = (rgb[i] < 0 || rgb[i] > 255);
	return (rgb);
}

short int *get_rgb(char *attr_buf, bool *err)
{
	char **rgb_buf;
	short int *rgb;

	rgb_buf = ft_split(attr_buf, ',');
	if (!str_is_float(rgb_buf[0]) || !str_is_float(rgb_buf[1]) || \
		!str_is_float(rgb_buf[2]))
		*err = true;
	rgb = save_rgb(rgb_buf, err);
	ft_free_matrix(rgb_buf);
	return (rgb);
}
/*this functions returns true on success*/

/* returns a t_coord pointer to t_coord struct*/
void	save_coords(t_coord *coord ,char **floats_buf, bool *err)
{
	coord->x = ft_mod_atof(floats_buf[0], err);
	coord->y = ft_mod_atof(floats_buf[1], err);
	coord->z = ft_mod_atof(floats_buf[2], err);
}

t_coord *get_coords(char *str_coords)
{
	char	**floats_buf;
	t_coord *return_coord;
	bool	err;

	floats_buf = ft_split(str_coords, ',');
	err = false;
	if (!floats_buf)
		return (NULL);
	else if (!str_is_float(floats_buf[0]) || !str_is_float(floats_buf[1]) || \
			!str_is_float(floats_buf[2]))
		err = true;
	return_coord = ft_calloc(1, sizeof(t_coord));
	if ( !return_coord)
		err = true;
	else
		save_coords(return_coord, floats_buf, &err);
	ft_free_matrix(floats_buf);
	if (err)
	{
		free(return_coord);
		return (NULL);
	}
	return (return_coord);
}

t_coord	*orientation_vector(char *str_cords)
{
	t_coord	*coord;

	coord = get_coords(str_cords);
	if (coord)
	{
		if (coord->x < -1.00 || coord->x > 1.00 || coord->y < -1.00 || \
			coord->y > 1.00 || coord->z < -1.00 || coord->z > 1.00)
		{
			free(coord);
			coord = NULL;
		}
	}
	return (coord);
}

bool	not_in_ambient_ratio(float ratio)
{
	return (ratio < 0.00 || ratio > 1.00);
}

void	ambient_light_cleaner(t_ambient *ambient)
{
	if (!ambient)
		return ;
	free(ambient->rgb);
	ambient->rgb = NULL;
}

bool	parse_ambient_ligth(t_program *program)
{
	bool		err;

	err = false;
	if (program->ambient)
		return (false);
	program->ambient = ft_calloc(1, sizeof(t_ambient));
	if (!program->ambient)
		return (false);
	program->ambient[0] = (t_ambient){NULL, 0.00};
	if (!str_is_float(program->attr_buf[1]) && \
		ft_word_count(program->attr_buf[2], ',') != 3)
		return (false);
	program->ambient->ratio = ft_mod_atof(program->attr_buf[1], &err);
	program->ambient->rgb = get_rgb(program->attr_buf[2], &err);
	if (err || not_in_ambient_ratio(program->ambient->ratio))
		ambient_light_cleaner(program->ambient);
	return (err == false);
}

bool	is_not_fov(float fov)
{
	return (fov < 0.00 || fov > 180.00);
}

void camera_cleaner(t_camera *camera)
{
	if (!camera)
		return ;
	free(camera->center);
	camera->center = NULL;
	free(camera->orientation);
	camera->orientation = NULL;
}

bool	parse_camera(t_program *program)
{
	bool		err;

	err = false;
	if (program->camera)
		return (false);
	program->camera = ft_calloc(1, sizeof(t_camera));
	if (!program->camera)
		return (false);
	program->camera[0] = (t_camera){NULL, NULL, 0.00};
	if (ft_word_count(program->attr_buf[1], ',') != 3 || \
		ft_word_count(program->attr_buf[2], ',') != 3 || \
		!str_is_float(program->attr_buf[3]))
		return (false);
	program->camera->center = get_coords(program->attr_buf[1]);
	program->camera->orientation = orientation_vector(program->attr_buf[2]);
	program->camera->fov = ft_mod_atof(program->attr_buf[3], &err);
	if (!program->camera->center || !program->camera->orientation || \
		err || is_not_fov(program->camera->fov))
		camera_cleaner(program->camera);
	return (err == false);
}

void light_cleaner(t_light *light)
{
	if (!light)
		return ;
	free(light->point);
	light->point = NULL;
}

bool parse_light(t_program *program)
{
	bool err;

	err = false;
	if (program->light)
		return (false);
	program->light = ft_calloc(1, sizeof(t_light));
	if (!program->light)
		return (false);
	program->light[0] = (t_light){NULL, 0.00};
	if (ft_word_count(program->attr_buf[1], ',') != 3 || \
		!str_is_float(program->attr_buf[2]))
		return (false);
	program->light->point = get_coords(program->attr_buf[1]);
	program->light->ratio = ft_mod_atof(program->attr_buf[2], &err);
	if (err || not_in_ambient_ratio(program->light->ratio))
		light_cleaner(program->light);
	return (err == false);
}

bool cylinder_basic_parse(t_program *program)
{
	return (ft_word_count(program->attr_buf[1], ',') != 3 || \
		ft_word_count(program->attr_buf[2], ',') != 3 || \
		!str_is_float(program->attr_buf[3]) || \
		!str_is_float(program->attr_buf[4]) || \
		ft_word_count(program->attr_buf[5], ',') != 3);
}

void cylinder_cleaner(t_cylinder *cylinder)
{
	if (!cylinder)
		return ;
	free(cylinder->center);
	free(cylinder->vector);
	free(cylinder->rgb);
	free(cylinder);
}

bool get_cylinder_data(t_cylinder *cylinder, t_program *program)
{
	bool err;

	err = false;
	cylinder->center = get_coords(program->attr_buf[1]);
	cylinder->vector = orientation_vector(program->attr_buf[2]);
	cylinder->diameter = ft_mod_atof(program->attr_buf[3], &err);
	cylinder->height = ft_mod_atof(program->attr_buf[4], &err);
	cylinder->rgb = get_rgb(program->attr_buf[5], &err);
	if (!cylinder->center || !cylinder->vector || err || !cylinder->rgb)
	{
		cylinder_cleaner(cylinder);
		return (false);
	}
	return (true);
}

bool parse_cylinder(t_program *program)
{
	t_cylinder *cylinder;
	t_list *new;

	if (cylinder_basic_parse(program))
		return (false);
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (false);
	*cylinder = (t_cylinder){NULL, NULL, 0.00, 0.00, 0.00, NULL};
	if (!get_cylinder_data(cylinder, program))
		return (false);
	new = ft_mod_lstnew(CYLINDER, cylinder);
	if (!new)
		return (false);
	ft_lstadd_back(&program->geometries, new);
	return (true);
}

bool plane_basic_parse(t_program *program)
{
	return (ft_word_count(program->attr_buf[1], ',') != 3 || \
		ft_word_count(program->attr_buf[2], ',') != 3 || \
		ft_word_count(program->attr_buf[3], ',') != 3);
}

void plane_cleaner(t_plane *plane)
{
	if (!plane)
		return ;
	free(plane->point);
	free(plane->normal);
	free(plane->rgb);
	free(plane);
}

bool get_plane_data(t_plane *plane, t_program *program)
{
	bool err;

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

bool parse_plane(t_program *program)
{
	t_plane *plane;
	t_list *new;

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

bool sphere_basic_parse(t_program *program)
{
	return (ft_word_count(program->attr_buf[1], ',') != 3 || \
		!str_is_float(program->attr_buf[2]) || \
		ft_word_count(program->attr_buf[3], ',') != 3);
}

void sphere_cleaner(t_sphere *sphere)
{
	if (!sphere)
		return ;
	free(sphere->center);
	free(sphere->rgb);
	free(sphere);
}

bool get_sphere_data(t_sphere *sphere, t_program *program)
{
	bool err;

	err = false;
	sphere->center = get_coords(program->attr_buf[1]);
	sphere->diameter = ft_mod_atof(program->attr_buf[2], &err);
	sphere->rgb = get_rgb(program->attr_buf[3], &err);
	if (!sphere->center || err || !sphere->rgb)
	{
		sphere_cleaner(sphere);
		return (false);
	}
	return (true);
}

bool parse_sphere(t_program *program)
{
	t_sphere	*sphere;
	t_list		*new;

	if (sphere_basic_parse(program))
		return(false);
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (false);
	*sphere = (t_sphere){NULL, 0.00, 0.00, NULL};
	if (!get_sphere_data(sphere, program))
		return (false);
	new = ft_mod_lstnew(SPHERE, sphere);
	if (!new)
		return (false);
	ft_lstadd_back(&program->geometries, new);
	return (true);
}

short int is_rt_element(char **attr_buf)
{
	size_t m_len;
	size_t str_len;

	if (!attr_buf)
		return (-1);
	m_len = ft_matrix_len(attr_buf);
	str_len = ft_strlen(attr_buf[0]);
	if (!ft_strncmp(attr_buf[0], "A", str_len) && m_len == N_DATA_A)
		return (AMBIENT_LIGTH);
	else if (!ft_strncmp(attr_buf[0], "C", str_len) && m_len == N_DATA_CA)
		return (CAMERA);
	else if (!ft_strncmp(attr_buf[0], "L", str_len) && m_len == N_DATA_L)
		return (LIGHT);
	else if (!ft_strncmp(attr_buf[0], "cy", str_len) && m_len == N_DATA_CY)
		return (CYLINDER);
	else if (!ft_strncmp(attr_buf[0], "p", str_len) && m_len == N_DATA_P)
		return (PLANE);
	else if (!ft_strncmp(attr_buf[0], "sp", str_len) && m_len == N_DATA_SP)
		return (SPHERE);
	return (-1);
}

void free_program_data(t_program *program)
{
	if (!program)
		return ;
	camera_cleaner(program->camera);
	free(program->camera);
	light_cleaner(program->light);
	free(program->light);
	ambient_light_cleaner(program->ambient);
	free(program->ambient);
	ft_modlstclear(program->geometries);
}

t_program get_attributes(char **all_file, bool *error)
{
	t_program program;
	unsigned int i;
	short int element;

	program = (t_program){NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0};
	bool (*function[6])(t_program *);
	function[AMBIENT_LIGTH] = parse_ambient_ligth;
	function[CAMERA] = parse_camera;
	function[LIGHT] = parse_light;
	function[CYLINDER] = parse_cylinder;
	function[PLANE] = parse_plane;
	function[SPHERE] = parse_sphere;
	i = -1;
	while(all_file[++i] && !*error)
	{
		program.attr_buf = ft_split(all_file[i], ' ');
		element = is_rt_element(program.attr_buf);
		if (element >= 0)
			*error = !function[element](&program);
		ft_free_matrix(program.attr_buf);
	}
	if (*error)
		free_program_data(&program);
	return (program);
}
