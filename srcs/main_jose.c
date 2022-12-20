/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_jose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:45:59 by jalvarad          #+#    #+#             */
/*   Updated: 2022/12/20 19:53:34 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_program process_data(char **file, bool *err)
{
	t_program program;

	if (*err)
		return ((t_program){NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0});
	program = get_attributes(file, err);
	if (!are_basic_attr(program) || *err)
		free_program_data(&program);
	program.n_geometries = ft_lstsize(program.geometries);
	program.shapes = lst_to_array(program.geometries, program.n_geometries);
	if ( !program.shapes && program.n_geometries )
	{
		free_program_data( &program );
		*err = 1;
	}
	else
		ft_modlstclear(program.geometries);
	program.geometries = NULL;
	return (program);
}

char** open_read(char *file_name, char **err_message)
{
	int fd;
	char **file;

	file = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd < 0 )
		*err_message = ft_strdup(ERR_C);
	//else	
		file = read_file(fd);
	close(fd);
	return (file);
}

char **basic_parser(int argc, char **argv, char **err_message)
{
	char **file;

	file = NULL;
	if (argc != 2)
		*err_message = ft_strdup(ERR_A);
	else if (!file_format(argv[1]))
		*err_message = ft_strdup(ERR_B);
	else
		file = open_read(argv[1], err_message);
	return (file);
}

void print_error(char *message)
{
	printf("ERROR\n");
	if (message)
		printf("%s\n", message);
	else
		printf("ME FALTA crear el mensaje por defecto");
}
int main(int argc, char **argv)
{
	t_program program;
	char **file;
	bool err;
	char *err_message;

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
	free_program_data(&program);
	return (0);
}

/*int main ()
{
	printf ("-------------- PRUEBAS FILE FORMAT ------------------ \n");
	printf ("%d \n", file_format("holala"));
	printf ("%d \n", file_format("holala.rt"));
	printf ("%d \n", file_format(".rt"));
	printf ("%d el vacio\n", file_format(""));
	printf ("%d \n", file_format(".r"));
	printf ("%d \n", file_format("holala.wx"));
	printf ("%d \n", file_format("123456789123456789.rt"));

	bool out_of_range = 0;
	printf ("-------------- PRUEBAS ATOF -------------------\n");
	printf ("%f   %d\n", ft_mod_atof("12345.12341234", &out_of_range), out_of_range);
	printf ("%f   %d\n", ft_mod_atof("+-12345.12341234", &out_of_range), out_of_range);
	printf ("%f   %d\n", ft_mod_atof("      -12345.12341234    ", &out_of_range), out_of_range);
	printf ("%f   %d\n", ft_mod_atof("      -1234512345678.12341234    ", &out_of_range), out_of_range);


	printf ("-------------- PRUEBAS READER  -------------------\n");
	int i = open("srcs/test.rt", O_RDONLY);
	printf("%d --- fd\n", i);
	char **all_file  = read_file(i);
	if (!all_file)
		return (1);
	for (int a = 0; all_file[a]; a++ )
		printf("|%s|\n", all_file[a]);
	close(i);
}*/