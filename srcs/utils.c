/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:33:10 by jalvarad          #+#    #+#             */
/*   Updated: 2022/12/06 16:09:21 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
