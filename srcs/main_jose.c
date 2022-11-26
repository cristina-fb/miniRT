/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_jose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:45:59 by jalvarad          #+#    #+#             */
/*   Updated: 2022/11/26 17:08:28 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_program process_data(char **file)
{
    t_program program;
    bool err;

    err = 0;
    program = get_attributes(file, &err);
    if (!are_basic_attr(program) || err)
        free_program_data(&program);
    program.n_geometries = ft_lstsize(program.geometries);
    program.shapes = lst_to_array(program.geometries, program.n_geometries);
    if ( !program.shapes && program.n_geometries)
        ;
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
    program = process_data(file);
    return (0);
}

// TODO = falta parsear que los atributos con letras mayusculas no sean NULL
// Devolver mensajes de error: utilizando perror y stderror
// convertir en un array las geometrias
//
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