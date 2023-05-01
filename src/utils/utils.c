/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:33:10 by jalvarad          #+#    #+#             */
/*   Updated: 2023/05/01 12:57:07 by jalvarad         ###   ########.fr       */
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

void	print_default_instructions(void)
{
	printf("Please make sure the map has the established format.\n");
	printf("Elements defined by an uppercase must only be declared once\n");
	printf("Ambient lightning:\n");
	printf("	%s \n	%s\n	%s\n", AMB_IDX, AMB_RATIO, RGB_MSG);
	printf("Camera:\n");
	printf("	%s\n 	%s\n	%s %s\n	%s\n", CM_IDX, CM_VP, \
			ORIENTATION, OR_RG, FOV);
	printf("Light:\n");
	printf("	%s\n 	%s\n	%s\n	%s\n", \
			L_IDX, L_LP, L_BRIGHT, RGB_MSG);
	printf("sphere:\n");
	printf("	%s\n	%s\n	%s\n	%s\n", \
			SP_IDX, SP_CENTER, SP_DIAMETER, RGB_MSG);
	printf("plane:\n");
	printf("	%s\n	%s %s\n	%s\n", PL_IDX, ORIENTATION, OR_RG, RGB_MSG);
	printf("cylinder:\n");
	printf("	%s\n	%s\n	%s %s\n", \
			CY_IDX, CY_COORDS, ORIENTATION, OR_RG);
	printf("	%s\n	%s\n", CY_DIAMETER, CY_HEIGHT);
	printf("For an example, please, ");
	printf("go to a file in the \"example_files\" folder\n");
}

void	print_error(char *message)
{
	printf("ERROR\n");
	if (message)
		printf("%s\n", message);
	else
		print_default_instructions();
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
		array[i].last_dist = 0.0;
		array[i].skip = 0;
		lst = lst->next;
		i++;
	}
	return (array);
}
