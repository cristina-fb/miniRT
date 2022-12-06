/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_jose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:45:59 by jalvarad          #+#    #+#             */
/*   Updated: 2022/12/06 16:26:48 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_program process_data(char **file, bool *err)
{
    t_program program;

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

int main(int argc, char **argv)
{
    t_program program;
    char **file;
    unsigned int fd;
    bool err;

    err = 0;
    if (argc != 2)
        return (0);
    else if (!file_format(argv[1]))
        return (0);
    fd = open(argv[1], O_RDONLY);
    file = read_file(fd);
    close(fd);
    if (!file)
        return (0);
    program = process_data(file, &err);
    if (err || !program.camera || !program.light || !program.ambient)
        free_program_data( &program );
    printf("ERROR!!\n");
    return (0);
}

// TODO =
// Devolver mensajes de error: utilizando perror y stderror
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