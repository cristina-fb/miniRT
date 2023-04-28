/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod_lstnew.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:45:23 by jalvarad          #+#    #+#             */
/*   Updated: 2023/02/01 12:41:16 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_mod_lstnew(short int type, void *content)
{
	t_list	*a;

	a = malloc(sizeof(t_list));
	if (!a)
		return (NULL);
	a->content = content;
	a->type = type;
	a->next = NULL;
	return (a);
}
