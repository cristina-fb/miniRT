/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:45:59 by jalvarad          #+#    #+#             */
/*   Updated: 2023/03/04 18:01:39 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_program	process_data(char **file, bool *err)
{
	t_program	program;

	if (*err)
		return ((t_program){NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0});
	program = get_attributes(file, err);
	if (!are_basic_attr(program) || *err)
		free_program_data(&program, true);
	program.n_geometries = ft_lstsize(program.geometries);
	program.shapes = lst_to_array(program.geometries, program.n_geometries);
	if (!program.shapes && program.n_geometries)
	{
		free_program_data(&program, true);
		*err = 1;
	}
	else
		ft_modlstclear(program.geometries, false);
	program.geometries = NULL;
	return (program);
}

char	**basic_parser(int argc, char **argv, char **err_message)
{
	char	**file;

	file = NULL;
	if (argc != 2)
		*err_message = ft_strdup(ERR_A);
	else if (!filename_format(argv[1]))
		*err_message = ft_strdup(ERR_B);
	else
		file = open_read(argv[1], err_message);
	return (file);
}
void    swap_primitives(t_llist *a, t_llist *b)
{
    t_llist tmp = *a;
    *a = *b;
    *b = tmp;
}

void generate_bounding_box(t_llist *primitives, int n_primitives) {
    for (int i = 0; i < n_primitives; i++) {
        t_bounding_box *bbox = (t_bounding_box *)malloc(sizeof(t_bounding_box));
		
		if (primitives[i].type == SPHERE)
			*bbox = get_bounding_box_sphere((t_sphere*)primitives[i].content);
		else if (primitives[i].type == PLANE)
			*bbox =get_bounding_box_plane((t_plane*)primitives[i].content);
		else if (primitives[i].type == CYLINDER)
			*bbox = get_bounding_box_cylinder((t_cylinder*)primitives[i].content);;
        primitives[i].bbox = bbox;
    }
}


void    build_bvh(t_llist *primitives, int n_primitives, t_bounding_box *bboxes, int depth)
{
    // Si solo hay una primitiva, se almacena su caja de límites y se devuelve
    if (n_primitives == 1)
    {
        bboxes[0] = *(primitives->bbox);
        return;
    }

    // Se elige un eje de división
    int axis = depth % 3;

    // Se ordenan las primitivas en base a su centro en el eje de división
    sort_primitives(primitives, n_primitives, axis);

    // Se dividen las primitivas en dos grupos
    int n_left = n_primitives / 2;
    int n_right = n_primitives - n_left;

    // Se construyen los dos sub-BVH recursivamente
    build_bvh(primitives, n_left, bboxes, depth + 1);
    build_bvh(primitives + n_left, n_right, bboxes + n_left, depth + 1);

    // Se almacena la caja de límites del sub-BVH actual
    t_bounding_box bbox_left = bboxes[0];
    t_bounding_box bbox_right = bboxes[n_left];

    // Se actualiza la caja de límites actual
    bboxes[0].min = min_coord(bbox_left.min, bbox_right.min);
    bboxes[0].max = max_coord(bbox_left.max, bbox_right.max);
}

void	raymarching(t_program *program)
{
	int		i;
	int		j;
	int		n;
	double	min;
	double	total;
	t_coord	point;
	t_llist	*aux;

	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			n = 0;
			total = 0;
			point = *program->camera->center;
			aux = NULL;
			while ((total < MAX_DIST) && (n++ < MAX_STEPS))
			{
				aux = min_distance(point, program, &min);
				if (aux)
					break ;
				total += min;
				point = v_add(point, v_mul(*program->camera->vp->arr[i][j].ray, min));
			}
			if (aux)
			{
				program->camera->vp->arr[i][j].color = pcolor(program, aux, &point, program->camera->vp->arr[i][j].ray);
			}
		}
	}
}

int	main(int argc, char **argv)
{
	clock_t start;

    start = clock();
	t_program	program;
	char		**file;
	bool		err;
	char		*err_message;

	err = 0;
	err_message = NULL;
	file = basic_parser(argc, argv, &err_message);
	err = err_message;
	program = process_data(file, &err);
	if (err || !program.camera || !program.light || !program.ambient)
	{
		print_error(err_message);
		free(err_message);
		return (0);
	}
	//print_program_data(program);
	raymarching(&program);
	open_window(program, start);
	return (0);
}
