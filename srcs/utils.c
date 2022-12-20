/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:33:10 by jalvarad          #+#    #+#             */
/*   Updated: 2022/12/20 20:25:17 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void print_program_data(t_program program)
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
	for( size_t i = 0; i < program.n_geometries ; i++ )
	{
		printf("type : %d\n", program.shapes[i].type);
	}
}

t_llist *lst_to_array(t_list *lst, size_t size)
{
	t_llist *array;
	unsigned int i;

	i = 0;
	if (!size)
		return (NULL);
	array = ft_calloc(size, sizeof(t_llist));
	if (!array)
		return(NULL);
	while (i < size)
	{
		array[i].content = lst->content;
		array[i].type = lst->type;
		lst = lst->next;
		i++;
	}
	return (array);
}

void	array_geometries_clear(t_llist *shapes, size_t len)
{
	size_t	i;

	i = 0;
	while(i < len)
	{
		printf("hollaaaa\n");
		if (shapes[i].type == CYLINDER)
			cylinder_cleaner(shapes[i].content);
		else if (shapes[i].type == SPHERE)
			sphere_cleaner(shapes[i].content);
		else if (shapes[i].type == PLANE)
			plane_cleaner(shapes[i].content);
		i++;
	}	
}

void	ft_modlstclear(t_list *lst)
{
	t_list *aux;

	while (lst)
	{
		aux = lst;
		if (lst->type == CYLINDER)
			cylinder_cleaner(lst->content);
		else if (lst->type == SPHERE)
			sphere_cleaner(lst->content);
		else if (lst->type == PLANE)
			plane_cleaner(lst->content);
		lst = lst->next;
		free(aux);
	}
}
