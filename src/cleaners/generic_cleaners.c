/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_cleaners.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:06:03 by jalvarad          #+#    #+#             */
/*   Updated: 2022/12/26 17:50:06 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Pass boolean on true delete content of every node
void	ft_modlstclear(t_list *lst, bool clean_content)
{
	t_list	*aux;

	while (lst)
	{
		aux = lst;
		if (clean_content)
		{
			if (lst->type == CYLINDER)
				cylinder_cleaner(lst->content);
			else if (lst->type == SPHERE)
				sphere_cleaner(lst->content);
			else if (lst->type == PLANE)
				plane_cleaner(lst->content);
		}
		lst = lst->next;
		free(aux);
	}
}

void	array_geometries_clear(t_llist *shapes, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (shapes[i].type == CYLINDER)
			cylinder_cleaner(shapes[i].content);
		else if (shapes[i].type == SPHERE)
			sphere_cleaner(shapes[i].content);
		else if (shapes[i].type == PLANE)
			plane_cleaner(shapes[i].content);
		i++;
	}	
}

// Pass boolean on true delete content of every node
void	free_program_data(t_program *program, bool clean_content)
{
	if (!program)
		return ;
	camera_cleaner(program->camera);
	free(program->camera);
	program->camera = NULL;
	light_cleaner(program->light);
	free(program->light);
	program->light = NULL;
	ambient_light_cleaner(program->ambient);
	free(program->ambient);
	program->ambient = NULL;
	ft_modlstclear(program->geometries, clean_content);
	program->geometries = NULL;
	array_geometries_clear(program->shapes, program->n_geometries);
	program->shapes = NULL;
}



