/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_jose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:45:59 by jalvarad          #+#    #+#             */
/*   Updated: 2023/02/04 16:21:45 by jalvarad         ###   ########.fr       */
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
	program.screen_height = RESOLUTION;
	program.screen_width = horizontal_resolution();
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
	}
	else
		print_program_data(program);
	/// ir al programa de generación de imagen
	free_program_data(&program, false);
	return (0);
}
