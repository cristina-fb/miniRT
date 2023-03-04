/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:33:10 by jalvarad          #+#    #+#             */
/*   Updated: 2023/03/03 18:49:54 by jalvarad         ###   ########.fr       */
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
	printf("Center: x -> %f , y -> %f , z -> %f\n", program.camera->center->x, program.camera->center->y, program.camera->center->z);
	printf("Orientation: x -> %f, y -> %f, z -> %f\n", program.camera->dir->x, program.camera->dir->y, program.camera->dir->z);
	printf("fov: %f \n", program.camera->fov);
	printf("------------------LIGHT----------------\n");
	printf("Pointer: x -> %f , y -> %f , z -> %f\n", program.light->point->x, program.light->point->y, program.light->point->z);
	printf("Ratio: %f \n", program.light->ratio);
	printf("rgb: %d  %d  %d\n", program.light->rgb[0], program.light->rgb[1], program.light->rgb[2]);
	printf("-----------------AMBIENT---------------\n");
	printf("rgb: %d  %d  %d\n", program.ambient->rgb[0], program.ambient->rgb[1], program.ambient->rgb[2]);
	printf("ratio: %f \n", program.ambient->ratio);
	printf("-----------------GEOMETRIES--------------\n");
	for (size_t i = 0; i < program.n_geometries ; i++)
	{
		printf("type : %d\n", program.shapes[i].type);
		//printf("COLOR %d\n", get_int_color(((t_sphere *)program.shapes[i].content)->rgb));
	}
}

void calc_sphere_bounding_box(t_sphere *sphere)
{
	sphere->min = ft_calloc(1, sizeof(t_coord));
	sphere->max = ft_calloc(1, sizeof(t_coord));
    sphere->min->x = sphere->center->x - sphere->radius;
    sphere->min->y = sphere->center->y - sphere->radius;
    sphere->min->z = sphere->center->z - sphere->radius;
    
    sphere->max->x = sphere->center->x + sphere->radius;
    sphere->max->y = sphere->center->y + sphere->radius;
    sphere->max->z = sphere->center->z + sphere->radius;
}

void		calc_cylinder_min_max(t_cylinder *cyl)
{
	cyl->min = ft_calloc(1, sizeof(t_coord));
	cyl->max = ft_calloc(1, sizeof(t_coord));
	cyl->min->x = fmin(cyl->ba->x, cyl->bb->x) - cyl->radius;
	cyl->min->y = fmin(cyl->ba->y, cyl->bb->y) - cyl->radius;
	cyl->min->z = fmin(cyl->ba->z, cyl->bb->z) - cyl->radius;
	cyl->max->x = fmax(cyl->ba->x, cyl->bb->x) + cyl->radius;
	cyl->max->y = fmax(cyl->ba->y, cyl->bb->y) + cyl->radius;
	cyl->max->z = fmax(cyl->ba->z, cyl->bb->z) + cyl->radius;

}

void		calc_plane_min_max(t_plane *plane)
{
	plane->min = ft_calloc(1, sizeof(t_coord));
	plane->max = ft_calloc(1, sizeof(t_coord));
	plane->min->x = plane->point->x - MAX_DIST;
	plane->min->y = plane->point->y - MAX_DIST;
	plane->min->z = plane->point->z - MAX_DIST;
	plane->max->x = plane->point->x + MAX_DIST;
	plane->max->y = plane->point->y + MAX_DIST;
	plane->max->z = plane->point->z + MAX_DIST;
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
		if (array[i].type == 3)
			calc_cylinder_min_max((t_cylinder *)array[i].content);
		else if(array[i].type == 4)
			calc_plane_min_max((t_plane *)array[i].content);
		else if(array[i].type == 5)
			calc_sphere_bounding_box((t_sphere *)array[i].content);
		lst = lst->next;
		i++;
	}
	return (array);
}
