/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_cleaners.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:06:03 by jalvarad          #+#    #+#             */
/*   Updated: 2023/05/05 18:12:06 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Pass boolean on true delete content of every node
void	ft_modlstclear(t_list *lst, bool clean_content)
{
	t_cleaner	cleaner[N_TYPES - 3];
	t_list		*aux;

	cleaners_charge(cleaner);
	while (lst)
	{
		aux = lst;
		if (clean_content)
			cleaner[lst->type - 3](lst->content);
		lst = lst->next;
		free(aux);
	}
}

void	array_geometries_clear(t_llist *shapes, size_t len)
{
	t_cleaner	cleaner[N_TYPES - 3];
	size_t		i;

	i = 0;
	cleaners_charge(cleaner);
	while (i < len)
	{
		cleaner[shapes[i].type - 3](shapes[i].content);
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
	free(program->shapes);
	program->shapes = NULL;
}
