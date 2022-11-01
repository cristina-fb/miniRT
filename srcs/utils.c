/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:33:10 by jalvarad          #+#    #+#             */
/*   Updated: 2022/11/01 14:58:46 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//// hay que modificarla, no tiene sentido tener tantos elementos de la lista,
t_list *lst_to_array(t_list *lst)
{
	t_list *array;
	unsigned int i;
	size_t size;

	i = 0;
	size = ft_lstsize(lst);
	if (!size)
		return (NULL);
	array = ft_calloc(size, sizeof(t_list));
	while (i < size)
	{
		array[i] = *lst;
		lst = lst->next;
		i++;
	}
	return (array);
}