/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:45:59 by jalvarad          #+#    #+#             */
/*   Updated: 2023/02/27 20:08:06 by jalvarad         ###   ########.fr       */
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
				printf("LIGHT: %d i = %d j= %d\n", program->camera->vp->arr[i][j].color, i, j);
			}
		}
	}
}

int	main(int argc, char **argv)
{
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
	open_window(program);
	return (0);
}
