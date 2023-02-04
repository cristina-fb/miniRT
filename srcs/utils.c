/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:33:10 by jalvarad          #+#    #+#             */
/*   Updated: 2023/01/25 12:54:11 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	filename_format(char *file_name)
{
	short int	start_sufix;
	short int	str_len;

	str_len = ft_strlen(file_name);
	start_sufix = str_len - 3;
	if (start_sufix >= 0 && str_len > 3)
		return (!ft_strncmp(file_name + start_sufix, ".rt", 3));
	return (false);
}

void	print_error(char *message)
{
	printf("ERROR\n");
	if (message)
		printf("%s\n", message);
	else
		printf("ME FALTA crear el mensaje por defecto"); //TODO
}

void	print_program_data(t_program program)
{
	printf("------------------CAMERA---------------\n");
	printf("Center: x ->%f , y ->%f , z ->%f\n", program.camera->center->x, program.camera->center->y, program.camera->center->z );
	printf("Orientation: x -> %f, y -> %f, z -> %f\n", program.camera->orientation->x, program.camera->orientation->y, program.camera->orientation->z);
	printf("fov: %f \n", program.camera->fov);
	printf("------------------LIGHT----------------\n");
	printf("Pointer: x ->%f , y ->%f , z ->%f\n", program.light->point->x, program.light->point->y, program.light->point->z);
	printf("Ratio: %f \n", program.light->ratio);
	printf("rgb: %d  %d   %d\n", program.light->rgb[0], program.light->rgb[1], program.light->rgb[2]);
	printf("-----------------AMBIENT---------------\n");
	printf("rgb: %d  %d   %d\n", program.ambient->rgb[0], program.ambient->rgb[1], program.ambient->rgb[2]);
	printf("ratio: %f \n", program.ambient->ratio);
	printf("-----------------GEOMETRIES--------------\n");
	for (size_t i = 0; i < program.n_geometries ; i++)
	{
		printf("type : %d\n", program.shapes[i].type);
	}
}

t_llist	*lst_to_array(t_list *lst, size_t size)
{
	t_llist			*array;
	unsigned int	i;

	i = 0;
	if (!size)
		return (NULL);
	array = ft_calloc(size, sizeof(t_llist));
	if (!array)
		return (NULL);
	while (i < size)
	{
		array[i].content = lst->content;
		array[i].type = lst->type;
		lst = lst->next;
		i++;
	}
	return (array);
}
